<?php

/*!
 * @file regexwikiforceconvert.h
 * @brief This file contains declaration of RegexWikiForceConvert class.
 * @author Mousa Moradi
 */

include_once('regex.php');
include_once('config.php');


/*!
 * @brief The Wiki force convert template checker Regex class.
 */
class RegexWikiForceConvert extends Regex
{
    /*!
     * @brief Class constructor
     * @param source The source text to work on it
     */
    public function __construct()
    {
		global $WIKI_FORCE_CONVERT_TAG;
		$this->pattern = "(?:\\`\\{\\`\\{\\s*" .
						 $WIKI_FORCE_CONVERT_TAG .
						 "\\s*\\|(?:[^\\`\\|]|\\`\\`)*" .
						 "\\|((?:[^\\`]|\\`\\`)*)" .
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
			//No conversion is needed:
			$this->matches['equivalent'][$i] = $this->matches[1][$i];
		}
	}
}

?>
