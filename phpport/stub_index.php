<?php include_once("lib/l2aconversion.php"); ?>
<html>
<head>
	<title>AzConvert-PHP - Transliterator for Azerbaijani language</title>
</head>
<body>

<?php
	$set = isset($_POST['source']);
	$wikiChecked = true;
	if ($set)
	{
		$wikiChecked = isset($_POST['wikimode']) && $_POST['wikimode'] == 'wiki';
		$convertor = new L2AConversion();
		$convertor->setOriginalText($_POST['source']);
		$convertor->convert($wikiChecked);
		$conv = $convertor->getConvertedResult();
	}
?>
	<div align="center">
		<form method="POST">
			<table>
				<tr>
					<td><textarea name="source" rows="25" cols="40"><?php if($set) echo $_POST['source']; else echo 'Səlam'; ?></textarea></td>
					<td><input type="checkbox" name="wikimode" value="wiki" <?php if ($wikiChecked) echo "checked=\"checked\""; ?> />Wiki<br/>
					<input type="submit" value="Convert" /></td>
					<td><textarea dir="rtl" rows="25" cols="40"><?php if($set) echo $conv; ?></textarea></td>
				</tr>
			</table>
		</form>
		<h3>The DB connection is slow! Please have patience.</h3>
		<h4>&copy;Copyright 2012 <a href="mailto:mousamk@gmail.com">Mousa Moradi</a></h4>
	</div>
</body>
</html>
