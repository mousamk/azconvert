<?php

include_once('config.php');


class DbService
{
	//Db connection:
	private $CON = 0;

	//The singleton instance of this class
	private static $instance = NULL;


	private function __construct()
	{
	}


	public static function getInstance()
	{
		if (NULL == self::$instance)
		{
			self::$instance = new DbService();
			self::$instance->loadDb();
		}

		return self::$instance;
	}


	private function loadDb()
	{
		global $host;
		global $user;
		global $password;
		global $database;
		
		
		$this->CON = mysql_connect($host, $user, $password);
		if (!$this->CON)
			die ('Could not connect to db: ' . mysql_error());
	
		mysql_select_db($database, $this->CON);
		mysql_query("SET CHARACTER SET UTF8;", $this->CON);
	}


	public function getCharacters($tablePostfix, &$table)
	{
		if($this->CON)
		{
			global $tablesPrefixes;
			
			$query = "SELECT * FROM " . $tablesPrefixes . "characters" . $tablePostfix . ";";
			$res = mysql_query($query, $this->CON);
			while($row = mysql_fetch_array($res))
			{
				$table[$row['source']] = $row;
			}
		}
	}


	public function getWords($tablePostfix, &$words)
	{
		if($this->CON)
		{
			global $tablesPrefixes;
			
			$query = "SELECT * FROM " . $tablesPrefixes . "words" . $tablePostfix . ";";
			$res = mysql_query($query, $this->CON);
			while($row = mysql_fetch_array($res))
			{
				$words[$row['source']] = $row;
			}
		}
	}


	public function getSolidWords($tablePostfix, &$solidWords)
	{
		if($this->CON)
		{
			global $tablesPrefixes;
			
			$query = "SELECT * FROM " . $tablesPrefixes . "solid_words" . $tablePostfix . ";";
			$res = mysql_query($query, $this->CON);
			while($row = mysql_fetch_array($res))
			{
				array_push($solidWords, $row['source']);
			}
		}
	}


	public function getSpecialChars($tablePostfix, &$specialChars)
	{
		if($this->CON)
		{
			global $tablesPrefixes;
			
			$query = "SELECT * FROM " . $tablesPrefixes . "special_characters" . $tablePostfix . ";";
			$res = mysql_query($query, $this->CON);
			while($row = mysql_fetch_array($res))
			{
				$specialChars[$row['id']] = $row;
			}
		}
	}


	public function getPrefixes($tablePostfix, &$prefixes)
	{
		$this->loadPostOrPrefix("prefix", $tablePostfix, $prefixes);
	}


	public function getPostfixes($tablePostfix, &$postfixes)
	{
		$this->loadPostOrPrefix("postfix", $tablePostfix, $postfixes);
	}


	public function loadPostOrPrefix($postOrPrefix, $tablePostfix, &$postOrPrefixes)
	{
		if($this->CON)
		{
			global $tablesPrefixes;
			
			$query = "SELECT * FROM " . $tablesPrefixes . $postOrPrefix . $tablePostfix . ";";
			$res = mysql_query($query, $this->CON);
			while($row = mysql_fetch_array($res))
			{
				$postOrPrefixes[$row['id']] = $row;
			}
		}
	}
}
?>
