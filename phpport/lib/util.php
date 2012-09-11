<?php
/*!
 * @file util.h
 * @brief This file contain declaration or definition of some utilities to be used
 *  in the files which needs them.
 *
 * @author Mousa Moradi
 */

class Util
{
	public static function is_even($p)
	{
		return ($p % 2 == 0);
	}
	
	
	public static function mb_str_replace($haystack, $needle, $replacement)
	{
		//return implode($replacement, mb_split($needle, $haystack));
		return str_replace($needle, $replacement, $haystack);
	}


	public static function to_lower($w)
	{
		$lw = $w;
		$lw = Util::mb_str_replace($lw, 'I', 'ı');
		$lw = Util::mb_str_replace($lw, 'İ', 'i');
		$lw = Util::mb_str_replace($lw, 'Ə', 'ə');
		$lw = Util::mb_str_replace($lw, 'Ö', 'ö');
		$lw = Util::mb_str_replace($lw, 'Ü', 'ü');
		$lw = Util::mb_str_replace($lw, 'Ğ', 'ğ');
		$lw = Util::mb_str_replace($lw, 'Ç', 'ç');
		$lw = Util::mb_str_replace($lw, 'Ş', 'ş');
		$lw = strtolower($lw);
		
		return $lw;
	}
	
	
	public static function endsWith($word, $part)
	{
		$partLen = mb_strlen($part, 'UTF-8');
		return mb_substr($word, -$partLen, $partLen, 'UTF-8')===$part;
	}
	
	
	public static function startsWith($word, $part)
	{
		$length = mb_strlen($part, 'UTF-8');
		return (mb_substr($word, 0, $length, 'UTF-8') === $part);
	}
	
	
	public static function is_digit($c)
	{
		return
			($c === 1 || $c === 2 || $c === 3 || $c === 4 || $c === 5 ||
			 $c === 6 || $c === 7 || $c === 8 || $c === 9 || $c === 0);
	}
}

?>
