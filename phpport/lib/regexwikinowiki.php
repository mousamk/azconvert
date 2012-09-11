<?php

/*!
 * @file regexwikinowiki.h
 * @brief This file contains declaration of RegexWikiNoWiki class.
 * @author Mousa Moradi
 */

include_once('convertor.php');
include_once('regex.php');


/*!
 * @brief The Wiki NoConvert template checker Regex class.
 */
class RegexWikiNoWiki extends Regex
{
    /*!
     * @brief Class constructor
     * @param source The source text to work on it
     * @param convertor The convertor engine which may be used to convert some pieces
     */
    public function __construct($convertor)
    {
		$this->convertor = $convertor;
		
		$this->pattern = "\\<nowiki\\>(.*)\\<\\/nowiki\\>";
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
		$count = count($this->matches[0]);
		for($i=0; $i<$count; $i++)
		{
			//Convert the inner text and a non-wiki text:
			$this->convertor->setOriginalText($this->matches[1][$i]);
			$inner = $this->convertor->convert(false);
			$equivalent = "<nowiki>$inner</nowiki>";
			
			$this->matches['equivalent'][$i] = $equivalent;
		}		
	}


    //! @brief Convertor used to convert pieces
    private $convertor;
}

?>
