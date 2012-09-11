<?php
/*!
 * @file convertor.h
 * @brief This files contains declaration of Convertor class.
 *
 * @author Mousa Moradi
 */

include_once('dbservice.php');

/*!
 * @class Convertor
 * @brief This class is the base class of convertor classes, specifies their interface,
 *  and implements common features.
 */
abstract class Convertor
{
    /*!
     * @brief Class constructor
     */
    function __construct()
    {
	}
    
    /*!
     * @brief Class destructor
     */
    function __destruct()
    {
	}
    
    /*!
     * @brief Converts the previously set original text and returns the result.
     * @param wikiMode Indicates whether the text be treated as wiki format and
     *        the required consideration be done or not
     * @return The converted result
     */
    abstract public function convert($wikiMode);

    /* !
     * @brief Converts a text without considering progress dialog.
     * @param text The text to be converted.
     * @param wikiMode Indicates whether the text be treated as wiki format and
     *        the required consideration be done or not
     * @return The converted result
     */
    //abstract public function convertText($text, $wikiMode);
    
    /*!
     * @brief Reloads the database resource.
     * @param force Indicates whether the reloading must be done ignoring conditions or not
     */
    public function reloadResources($force)
    {
		$postfix = $this->getTablesPostfix();
		if ($force || self::$loadedMode != $postfix)
		{
			$this->loadChars();
			$this->loadWords();
			$this->loadSolidWords();
			$this->loadPrefixes();
			$this->loadPostfixes();
			$this->loadSpecialChars();

			self::$loadedMode = $postfix;
		}
	}
    
    /*!
     * @brief Sets the original text to be used later in converting.
     * @param text The orginial text to be converted later
     */
    public function setOriginalText($text)
    {
		$this->strSource = $text;
	}

    /*!
     * @brief Gets the converted result
     * @return Returns the converted result
     */
    public function getConvertedResult()
    {
		return $this->strResult;
	}
    

    /*!
     * @brief Returns the words collection.
     * @return The words collection
     */
    public function &getWords()
    {
		return self::$words;
	}


    /*!
     * @brief Gets the convertor's postfix for database tables
     * @returns The postfix of the convertor in db tables
     */
    abstract public function getTablesPostfix();


    //! @brief Loads character table used for base transliteration
    protected function loadChars()
    {
		self::$chars = array();
		DbService::getInstance()->getCharacters($this->getTablesPostfix(), self::$chars);
		
		//echo "CHARS NOW:"; var_dump(self::$chars); echo "<br/><br/>";
	}


    //! @brief Loads special character conversion table for transliteration
    protected function loadSpecialChars()
    {
		self::$specialChars = array();
		DbService::getInstance()->getSpecialChars($this->getTablesPostfix(), self::$specialChars);
	}


    //! @brief Loads words table used in transliteration
    protected function loadWords()
    {
		self::$words = array();
		DbService::getInstance()->getWords($this->getTablesPostfix(), self::$words);
	}


    //! @brief Loads solid words table
    protected function loadSolidWords()
    {
		self::$solidWords = array();
		DbService::getInstance()->getSolidWords($this->getTablesPostfix(), self::$solidWords);
	}


    //! @brief Loads prefixes table used in transliteration
    protected function loadPrefixes()
    {
		self::$prefixes = array();
		DbService::getInstance()->getPrefixes($this->getTablesPostfix(), self::$prefixes);
	}


    //! @brief Loads postfixes table used in transliteration
    protected function loadPostfixes()
    {
		self::$postfixes = array();
		DbService::getInstance()->getPostfixes($this->getTablesPostfix(), self::$postfixes);
	}

    
    //! @brief The original source text to be converted
    protected $strSource;

    //! @brief The converted text
    protected $strResult;

    //! @brief The transliteration table of characeters
    static protected $chars;

    //! @brief The transliteration table of special characters
    static protected $specialChars;

    //! @brief Table of words and their equivalents used for conversion
    static protected $words;

    //! @brief List of non-convertible words
    static protected $solidWords;

    //! @brief Table of prefixes and their related fields
    static protected $prefixes;

    //! @brief Table of postfixes and their related fields
    static protected $postfixes;

    //! @brief The loaded mode's table postfix will be saved in this when db data are loaded:
    static protected $loadedMode;
};

?>
