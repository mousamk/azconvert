<?php

/*!
 * @file regexwikinoconvert.h
 * @brief This file contains declaration of RegexWikiNoConvert class.
 * @author Mousa Moradi
 */

include_once('regex.php');
include_once('config.php');


/*!
 * @brief The Wiki NoConvert template checker Regex class.
 */
class RegexWikiNoConvert extends Regex
{
    /*!
     * @brief Class constructor
     * @param source The source text to work on it
     * @param convertor The convertor engine which may be used to convert some pieces
     */
    public function __construct()
    {
		global $WIKI_NO_CONVERT_TAG;
		$this->pattern = "(?:\\`\\{\\`\\{\\s*" .
						 $WIKI_NO_CONVERT_TAG .
						 "\\s*\\|\\s*((?:[^\\`]|\\`\\`)*)" .
						 "\\`\\}\\`\\})";
        $this->pattern = '#' . $this->pattern . '#';
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
			//Set the first parameter as result:
			$this->matches['equivalent'][$i] = $this->matches[1][$i];
		}
	}
}

?>
