<?php

include_once('convertor.php');
include_once('util.php');
include_once('regexurl.php');
include_once('regexemail.php');
include_once('regexhtmltag.php');
include_once('regexwikilink.php');
include_once('regexwikiinterwiki.php');
include_once('regexwikinoconvert.php');
include_once('regexwikipicture.php');
include_once('regexwikiforceconvert.php');
include_once('regexwikinowiki.php');
include_once('regexwikitemplate.php');


class L2AConversion extends Convertor
{
    public function __construct()
    {
		Convertor::reloadResources(false);
	}
	
	
    public function convert($wikiMode)
    {
		//Pre process text:
		$this->preprocessText($wikiMode);

		//Convert the preprocessed text:
		$this->strResult = $this->convertText($this->strSource);

		//Post process result:
		$this->postprocessText();

		return $this->strResult;
	}
	
	
    public function setOriginalText($text)
    {
		Convertor::setOriginalText($text);
		$this->strResult = '';
	}
	
	
    public function getTablesPostfix()
    {
		return '_l2a';
	}
    

    private function convertText($text)
    {
		//echo "CONVERTING TEXT: $text <br/><br/>";
		$res = '';
		$length = mb_strlen($text, self::$ENC);
		$i = 0;
		$bracket = false;       //Beware of this in non-wiki mode!
		while ($i < $length)
		{
			$word = $this->getWord($i, $text);
			//echo "GOT WORD: $word i: $i<br/><br/>";
			$preLastChar = mb_substr($text, $i-1, 1, self::$ENC);
			$bracket = $i>0 && ($preLastChar == ']' || $preLastChar=='}');
			//echo "i:$i";
			$i += mb_strlen($word, self::$ENC);
			//echo "$word-i:$i<br/>";

			$res .= $this->convertWord($word, $bracket);
			//echo "'" . mb_substr($text, $i, 1, self::$ENC) . "'<br/>";
			//echo !$this->isCharAInWordChar(mb_substr($text, $i, 1, self::$ENC)) ? "TRUE<br/>" : "FALSE<br/>";
			//echo $i < $length ? "TRUE<br/>" : "FALSE<br/>";

			while (($i < $length) && !$this->isCharAInWordChar(mb_substr($text, $i, 1, self::$ENC)))
			{
				$curChar = mb_substr($text, $i, 1, self::$ENC);
				//echo "CURRENT CHAR: $curChar <br/><br/>";

				//Converting characters:
				$ch = $this->getSpecialChar($curChar, $i);
				$res .= ($ch == '') ? $curChar : $ch;
				$i++;
			}
		}

		return $res;
	}


    /*!
     * @brief Converts the given word and returns the result
     * @param w The word to be converted
     * @param part Indicates whether it's a (right) part of another word, or
     *        is a standalone word.
     * @return The converted result
     */
    public function convertWord($w, $part)
    {
		if ('' == $w)
			return '';

		if (!$part && $this->isNonConvertableWord($w))
			return $w;


		$word = '';
		$word = Util::to_lower($w);
		$str = '';
		if (!$part) $str = $this->lookupWord($word);
		if ('' == $str)
		{
			//Separate and convert prefixes:
			$wordWithoutPrefixes = $word;
			$wordPrefixes = '';
			$wordDict = '';
			if (!$part)
			{
				$this->separatePrefixes($word, $wordWithoutPrefixes, $wordPrefixes);

				//Check remaning in dictionary:
				$wordDict = $this->lookupWord($wordWithoutPrefixes);
				if ('' != $wordDict)
				{
					$str = $wordPrefixes . $wordDict;
					return $str;
				}
			}

			//Separate and convert postfixes:
			$wordWithoutPostfixes = '';
			$wordPostfixes = '';
			$this->separatePostfixes($wordWithoutPrefixes, $part, $wordWithoutPostfixes, $wordPostfixes);

			//Check remaining in dictionary:
			if (!$part)
			{
				$wordDict = $this->lookupWord($wordWithoutPostfixes);
				if ('' != $wordDict)
				{
					$str = $wordPrefixes . $wordDict . $wordPostfixes;
					return $str;
				}
			}

			//Stick them together and form the final word:
			$word = $wordPrefixes . $wordWithoutPostfixes . $wordPostfixes;

			//Preprocess word:
			$word = $this->preprocessWord($word);

			//Use simple transliteration to convert the rest:
			$str = $this->convertWordSimple($word);
		}
		
		return $str;
	}


    /*!
     * @brief Converts a word with basic transliteration algorithm.
     * @param word The word to be converted
     * @return The converted result
     */
    private function convertWordSimple($word)
    {
		$str = '';
		$length = mb_strlen($word, self::$ENC);
		for ($i = 0; $i < $length; $i++)
		{
			//Choose letter position mode:
			$mode = 'mid';
			if (0 == $i) $mode = 'start';
			else if ($length-1 == $i) $mode = 'end';

			$c = mb_substr($word, $i, 1, self::$ENC);
			$eq = '';
			$this->getCharEquivalent($c, $mode, $eq);
			$str .= $eq;
		}

		return $str;
	}
	
	
    private function separatePostfixes($word, $part, &$nakedWord, &$wordPostfixes)
    {
		$nakedWord = $word;
		$wordPostfixes = '';
		if ('' == $word)
			return;

		$postfix = '';
		$hasVs = false;
		$removeLast = false;
		$offset = $part ? 0 : 3;
		reset(self::$postfixes);
		while(current(self::$postfixes) !== FALSE)
		{
			$record = current(self::$postfixes);
			$postfix = $record['source'];
			$hasVs = $removeLast = false;
			
			$nakedWordLength = mb_strlen($nakedWord, self::$ENC);
			$postfixLength = mb_strlen($postfix, self::$ENC);

			if ($nakedWordLength >= $postfixLength + $offset &&
					Util::endsWith($nakedWord, $postfix) &&
						 ($record['dict'] == 0 ||
							  ($record['dict']==1 &&
								  ''!=$this->lookupWord(mb_substr($nakedWord, 0, $nakedWordLength - $postfixLength), self::$ENC)
							  )
						 )
			   )
			{
				if (!$part)
				{
					switch ($record['type'])
					{
						case 1:
							//Nothing to do!
							break;

						case 2:
							if ($this->isSticking(mb_substr($nakedWord, $nakedWordLength - $postfixLength - 1, 1, self::$ENC)))
								$hasVs = true;
							break;

						case 3:
							if ('ə' == mb_substr($nakedWord, $nakedWordLength - $postfixLength - 1, 1, self::$ENC))
								$hasVs = true;
							break;

						case 4:
							if ('ə' == mb_substr($nakedWord, $nakedWordLength - $postfixLength - 1, 1, self::$ENC))
								$removeLast = true;
							break;
					}
				}

				$wordPostfixes = ($hasVs ? self::$VS : '') . $record['equivalent'] . $wordPostfixes;
				$nakedWord = mb_substr($nakedWord, 0, $nakedWordLength-$postfixLength, self::$ENC);
				if ($removeLast && !$part)
					$nakedWord = mb_substr($nakedWord, 0, $nakedWordLength-1, self::$ENC);

				//Check if the remaining word is in dictionary:
				if ('' != $this->lookupWord($nakedWord))
					return;
				else
				{
					reset(self::$postfixes);
					continue;
				}
			}
			
			next(self::$postfixes);
		}
	}
	
	
    private function separatePrefixes($word, &$nakedWord, &$wordPrefixes)
    {
		$nakedWord = $word;
		$wordPrefixes = '';
		if ('' == $word)
			return;

		$hasVs = false;
		$removeLast = false;
		$prefix = '';
		reset(self::$prefixes);
		while(current(self::$prefixes) !== FALSE)
		{
			$record = current(self::$prefixes);
			$prefix = $record['source'];
			
			$nakedWordLength = mb_strlen($nakedWord, self::$ENC);
			$prefixLength = mb_strlen($prefix, self::$ENC);

			if ($nakedWordLength > $prefixLength + 2 && Util::startsWith($nakedWord, $prefix))
			{
				switch ($record['type'])
				{
					case 1:
						//Nothing to do!
						break;

					case 2:
						if ($this->isSticking(mb_substr($prefix, $prefixLength - 1, 1, $this->VOC)))
							$hasVs = true;
						break;

					case 3:
						if ('ə' == mb_substr($prefix, $prefixLength - 1, 1, $this->VOC))
							$hasVs = true;
						break;

					case 4:
						if ('ə' == mb_substr($prefix, $prefixLength - 1, 1, $this->VOC))
							$removeLast = true;
						break;
				}

				$wordPrefixes .= $record['equivalent'];
				if ($removeLast)
					$wordPrefixes = mb_substr($wordPrefixes, 0, mb_strlen($wordPrefixes, $this->VOC)-1);
				$wordPrefixes .= ($hasVs ? $this->VS : "");
				$rightLen = $nakedWordLength - $prefixLength;
				$nakedWord = mb_substr($nakedWord, -$rightLen, $rightLen, $this->VOC);

				//Check if the remaining word is in dictionary:
				if ('' != $this->lookupWord($nakedWord))
					return;
				else
				{
					reset(self::$prefixes);
					continue;
				}
			}
			
			next(self::$prefixes);
		}
	}
	
	
    private function getSpecialChar($c, $index)
    {
		//QMap<int, SpecialCharacterRecord>::const_iterator i;
		reset(self::$specialChars);
		while(current(self::$specialChars) != FALSE)
		//for(i = specialChars.constBegin(); i != specialChars.constEnd(); i++)
		{
			$record = current(self::$specialChars);
			if($record['source'] == $c)
			{
				$position = $record['position'];
				if (0 == $position)
					return $record['equivalent'];
				else
				{
					$times = getCharacterCount($c, $index);
					if ((1 == $position && !Util::is_even($times)) || (2 == $position && Util::is_even($times)))
						return $record['equivalent'];
				}
			}
			
			next(self::$specialChars);
		}

		return '';
	}
	
	
    private function getWord($i, $source)
    {
		$word = '';
		$c = mb_substr($source, $i, 1, self::$ENC);
		$len = mb_strlen($source, self::$ENC);

		while ($this->isCharAInWordChar($c))
		{
			$word .= $c;
			$i++;

			if ($i >= $len)
				break;

			$c = mb_substr($source, $i, 1, self::$ENC);
		}

		return $word;
	}
	
	
    private function lookupWord($w)
    {
		if (isset(self::$words[$w]))
			return self::$words[$w]['equivalent'];
		else
			return '';
	}
	
	
    private function isCharAInWordChar($c)
    {
		$cLower = Util::to_lower($c);
		return isset(self::$chars[$cLower])         //It's in the characters table
				|| Util::is_digit($c)               //It's a digit
				|| 'w' == $cLower;                  //It has 'w'. This is necessary because this letter is not in characters table
	}
	
	
    private function isNonConvertableWord($w)
    {
		$lw = Util::to_lower($w);
		return (mb_strpos($lw, 'w', 0, self::$ENC) !== FALSE) || isset(self::$solidWords[$lw]);
	}
	
	
    private function isSticking($c)
    {
		$sticking = true;
		if (isset(self::$chars[$c])) $sticking = self::$chars[$c]['sticking'] != '0';

		return $sticking;
	}
	
	
    private function preprocessText($wikiMode)
    {
		//Changing "dr." to "dr ":
		$this->strSource = Util::mb_str_replace($this->strSource, 'dr.', 'dr'); 		//TODO: Do something to this to become case insensitive.

		//Escape every '\', '{' and '}' characters using `:
		$this->strSource = Util::mb_str_replace($this->strSource, '`', '``');
		$this->strSource = Util::mb_str_replace($this->strSource, '{', '`{');
		$this->strSource = Util::mb_str_replace($this->strSource, '}', '`}');

		//List of regex processors:
		$regexProcessors = array();
		if ($wikiMode) array_push($regexProcessors, new RegexWikiNoWiki(new L2AConversion()));
		if ($wikiMode) array_push($regexProcessors, new RegexWikiNoConvert());
		if ($wikiMode) array_push($regexProcessors, new RegexWikiForceConvert());
		array_push($regexProcessors, new RegexEmail());
		array_push($regexProcessors, new RegexUrl());
		if ($wikiMode) array_push($regexProcessors, new RegexWikiTemplate());
		if ($wikiMode) array_push($regexProcessors, new RegexWikiInterwiki());
		if ($wikiMode) array_push($regexProcessors, new RegexWikiLink(new L2AConversion()));
		if ($wikiMode) array_push($regexProcessors, new RegexWikiPicture(new L2AConversion()));
		array_push($regexProcessors, new RegexHtmlTag());


		//Run each one of the regex processors and collect its results:
		if (Regex::getHolderNumber() > 2000000000) Regex::reset();      //Just to be sure in. Here this cannot happen, but in php mode, it may!
		$change = true;
		$processorsCount = count($regexProcessors);
		while($change)
		{
			$change = false;
			for($i=0; $i<$processorsCount; $i++)
			{
				if ($regexProcessors[$i]->run($this->strSource))
				{
					$change = true;
					$this->replaces = array_merge($this->replaces, $regexProcessors[$i]->getResults());
				}
			}
		}

		//Delete the regex processors:
		for($i=$processorsCount-1; $i>=0; $i--)
		{
			unset($regexProcessors[$i]);
			//regexProcessors.removeLast(); 		//NOTE: Maybe needed!
		}
	}
	
	
    private function postprocessText()
    {
		//Replace back the place holder:
		$holder1 = '';
		$holder2 = '';
		$change = true;
		while($change)
		{
			$change = false;
			reset($this->replaces);
			while(current($this->replaces) != FALSE)
			{
				$current = current($this->replaces);
				$index = $current['id'];
				$holder1 = '{' . $this->convertWordSimple("$index") . '}';
				$holder2 = '{' . $index . '}';
				
				if(mb_strpos($this->strResult, $holder1, 0, self::$ENC) !== FALSE)
				{
					$this->strResult = Util::mb_str_replace($this->strResult, $holder1, $current['equivalent'], self::$ENC);
					$change = true;
				}
				else if(mb_strpos($this->strResult, $holder2, 0, self::$ENC) !== FALSE)
				{
					$this->strResult = Util::mb_str_replace($this->strResult, $holder2, $current['equivalent'], self::$ENC);
					$change = true;
				}
				
				next($this->replaces);
			}
		}

		//Remove escape characters:
		$this->strResult = Util::mb_str_replace($this->strResult, '`{', '{');
		$this->strResult = Util::mb_str_replace($this->strResult, '`}', '}');
		$this->strResult = Util::mb_str_replace($this->strResult, '``', '`');
	}
	
	
    private function preprocessWord($word)
    {
		$res = $word;
		
		//Add necessary 'i' to some words:
		if (mb_strlen($res, self::$ENC) > 2)
		{
			$start = mb_substr($res, 0, 2, self::$ENC);
			if ('sp' == $start ||
				'st' == $start ||
				'şp' == $start ||
				'şt' == $start ||
				'şk' == $start)
				$res = 'i' . $res;
		}

		$res = Util::mb_str_replace($res, 'iyi', 'igi');
		$res = Util::mb_str_replace($res, 'iyy', 'iy');
		$res = Util::mb_str_replace($res, 'iy', 'i');

		return $res;
	}
	
	
    private function getCharEquivalent($ch, $mode, &$equivalent)
    {
		if (isset(self::$chars[$ch]))
			$equivalent = self::$chars[$ch][$mode];
		else
		{
			$equivalent = $ch;
		}
	}
	
	
    private function getCharacterCount($character, $position)
    {
		$left = mb_substr($this->strSource, 0, $position+1, self::$ENC);
		return mb_substr_count($left, $character, self::$ENC);
	}
    
    
    //! @brief The virtual space string
    private static $VS = '‌';

    //! @brief Map of the placeholders to return them back
    private $replaces = array();
    
    //! @brief Encoding to be used in multibyte functions
    private static $ENC = 'UTF-8';
}

?>
