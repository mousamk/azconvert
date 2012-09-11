<?php

/*!
 * @file regexwikipicture.h
 * @brief This file contains declaration of RegexWikiPicture class.
 * @author Mousa Moradi
 */

include_once('convertor.php');
include_once('regex.php');
include_once('util.php');


/*!
 * @brief The Wiki picture checker Regex class.
 */
class RegexWikiPicture extends Regex
{
    /*!
     * @brief Class constructor
     * @param source The source text to work on it
     * @param convertor The convertor engine which may be used to convert some pieces
     */
    public function __construct($convertor)
    {
		$this->convertor = $convertor;
		
		$this->pattern =
				"(?:" .
					"\\[\\[\\s*(?:Şəkil|File)\\s*\\:" .
					"(?:([^\\]]*)\\|)*" .
					"(?:([^\\]\\|]*))" .
					"\\]\\]" .
				")|" .
				"(?:" .
					"\\n+(?:Şəkil|File)\\s*:" .
					"(?:([^\\n]*)\\|)*" .
					"(?:([^\\n\\|]*))" .
					"(?=\\n)" .
				")";
        $this->pattern = '#' . $this->pattern . '#i';
	}
	
	
	//! @brief Class destructor
	public function __destruct()
	{
		unset($convertor);
	}


    /*!
     * @brief Reads the regexp.cap() and gets the equivalent for the matched substrings
     * @return The equivalent for the matched substrings. It may be the same as first matched one.
     */
    protected function getMatchEquivalent()
    {
		$tempRegexp = (
					"(?:\\s*alt\\s*\\=.*)|" .
					"(?:\\s*link\\s*\\=.*)|" .
					"(?:" .
						"(?:\\s*[0-9]+\\s*px\\s*)|" .
						"(?:\\s*x\\s*[0-9]+\\s*px\\s*)|" .
						"(?:\\s*[0-9]+\\s*x\\s*[0-9]+\\s*px\\s*)|" .
						"(?:\\s*upright\\s*)|" .
						"(?:\\s*upright\\s*[0-9]*(?:\\.[0-9]+)?\\s*)" .
					")|" .
					"(?:" .
						"(?:right)|" .
						"(?:left)|" .
						"(?:center)|" .
						"(?:none)" .
					")|" .
					"(?:" .
						"\\s*(?:" .
							"(?:baseline)|" .
							"(?:middle)|" .
							"(?:sub)|" .
							"(?:super)|" .
							"(?:text\\-top)|" .
							"(?:text\\-bottom)|" .
							"(?:top)|" .
							"(?:bottom)" .
						")\\s*" .
					")|" .
					"(?:\\s*border\\s*)|" .
					"(?:" .
						"\\s*thumb(?:nail)?\\s*(?:\\=\\s*[^\\]\\|]*)?" .
					")");
		$tempRegexp = '#' . $tempRegexp . '#i';
		
		$count = count($this->matches[0]);
		for($i=0; $i<$count; $i++)
		{
			$wholeMatch = $this->matches[0][$i];
			$matchCount = count($this->matches);
			
			//Get the last part:
			$equivalent = $wholeMatch;
			if ($matchCount > 2)
			{
				$preLast = $this->matches[1][$i];
				$last = $this->matches[2][$i];
				if('' == $preLast && '' == $last && $matchCount>4)
				{
					$preLast = $this->matches[3][$i];
					$last = $this->matches[4][$i];
				}

				//Check if the last part is not a special field:
				$transliterate = true;

				//If it's matches:
				$tempMatches = array();
				preg_match($tempRegexp, $last, $tempMatches);
				$tempMatchesCount = count($tempMatches);
				if ($tempMatchesCount > 0)
				{
					if ($tempMatches[0] === $last)
						$transliterate = false;
				}

				if ($transliterate)
				{
					$equivalent = "Şəkil:" . $preLast . "|"; 			//TODO: Instead of 'Şəkil' put the correct one (Sekil, File, Sound, ...).
					$this->convertor->setOriginalText($last);
					$lastConverted = $this->convertor->convert(true);
					$equivalent .= $lastConverted; 
					if (Util::startsWith($wholeMatch, '[['))
						$equivalent = "[[" . $equivalent . "]]";
					if (Util::startsWith($wholeMatch, '\n'))
						$equivalent = "\n" . $equivalent;
					if (Util::endsWith($wholeMatch, '\n'))
						$equivalent .= "\n";
				}
				else
					$equivalent = $wholeMatch;
			}
			
			$this->matches['equivalent'][$i] = $equivalent;
		}		
	}


    //! @brief Convertor used to convert pieces
    private $convertor;
}

?>
