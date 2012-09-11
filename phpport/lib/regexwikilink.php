<?php

/*!
 * @file regexwikilink.h
 * @brief This file contains declaration of RegexWikiLink class.
 * @author Mousa Moradi
 */

include_once('convertor.php');
include_once('regex.php');


/*!
 * @brief The Wiki link checker Regex class.
 */
class RegexWikiLink extends Regex
{
    /*!
     * @brief Class constructor
     * @param source The source text to work on it
     */
    public function __construct($convertor)
    {
		$this->convertor = $convertor;
		
		$this->pattern = "\\[\\[([^\\|\\]\\:]+)(?:\\|([^\\]]+))?\\]\\]";
        $this->pattern = '#' . $this->pattern . '#';
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
		$count = count($this->matches[0]);
		for($i=0; $i<$count; $i++)
		{
			$link1 = $this->matches[1][$i];
			$link2 = $this->matches[2][$i];
			$link = '' == $link2 ? $link1 : $link2;
			$this->convertor->setOriginalText($link);
			$equivalent = $this->convertor->convert(false);
			$fullEqual = '[[' . $link1;
			if ($link1 !== $link2)
				$fullEqual .= '|' . $equivalent;
			$fullEqual .= ']]';
			
			$this->matches['equivalent'][$i] = $fullEqual;
		}		
	}


    //! @brief Convertor used to convert pieces
    private $convertor;
}

?>
