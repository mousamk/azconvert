<?php

/*!
 * @file regex.h
 * @brief This file contains declaration of abstract base Regex class.
 * @author Mousa Moradi
 */
 
include_once('util.php');
 

/*!
 * @brief The abstract base class for RegEx checker classes.
 */
abstract class Regex
{
    /*!
     * @brief Class constructor.
     * @param source The source text to work on it
     */
    public function __construct()
    {
	}

    /*!
     * @brief Class destructor.
     */
    public function __destruct()
    {
	}
	

    /*!
     * @brief This does the main job of search, extract and replace.
     * @returns Returns whether some match is found or not.
     */
    public function run(&$source)
    {
		$placesHeld = array();
		$this->matches = array();

		$match = '';
		$holder = '';

		$matchCount = preg_match_all($this->pattern, $source, $this->matches);
		$this->getMatchEquivalent();

		for($i=0; $i<$matchCount; $i++)
		{
			//Replace the url with a numbered place holder:
			array_push($this->placesHeld, array('equivalent' => $this->matches['equivalent'][$i], 'id' => self::$holderNumber));
			$holder = '{' . self::$holderNumber . '}';
			$source = Util::mb_str_replace($source, $this->matches[0][$i], $holder);
			self::$holderNumber++;
		}

		return $matchCount > 0;
	}

    /*!
     * @brief Gets the results.
     * @returns The results
     */
    public function getResults()
    {
		return $this->placesHeld;
	}

    /*!
     * @brief Resets the holder number
     */
    public static function reset()
    {
		$this->holderNumber = 1;
	}

    /*!
     * @brief Returns the holder number
     * @return The holder number
     */
    public static function getHolderNumber()
    {
		return self::$holderNumber;
	}


    /*!
     * @brief Reads the regexp.cap() and gets the equivalent for the matched substrings
     * @return The equivalent for the matched substrings. It may be the same as first matched one.
     */
    abstract protected function getMatchEquivalent();


    //! @brief This holds the place holder counter
    private static $holderNumber = 1;

    //! @brief The regular expression
    protected $pattern = '';
    
    //! @brief The found matches will be placed here
    protected $matches = array();

    //! @brief The extracted (and converted) substrings will be saved in this
    protected $placesHeld = array();
}

?>
