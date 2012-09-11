<?php

/*!
 * @file regexwikitemplate.h
 * @brief This file contains declaration of RegexWikiTemplate class.
 * @author Mousa Moradi
 */

include_once('regex.php');


/*!
 * @brief The Wiki template checker Regex class.
 */
class RegexWikiTemplate extends Regex
{
    /*!
     * @brief Class constructor
     * @param source The source text to work on it
     */
    public function __construct()
    {
		$this->pattern = "\\`\\{\\`\\{[^\\`]*\\`\\}\\`\\}";
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
			$this->matches['equivalent'][$i] = $this->matches[0][$i];
		}
	}
}

?>
