<!-- Common functions -->
<?php

	// ----- ExplicitURL ----- //

	function ExplicitURL ($url) {
		echo ("<a href=\"$url\">$url</a>");
	}

	// ----- ViewCvsURL ----- //

	function ViewCvsURL ($url, $link) {
		echo ("<a href=\"http://cvs.sourceforge.net/cgi-bin/viewcvs.cgi/blood/$url/\">$link</a>");
	}
?>


<!-- Common header -->
<?php
	echo ("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
	"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
	<meta http-equiv="content-type" content="text/html; charset=ISO-8859-1" />
	<link rel="icon" href="images/qblood_icon.png" type="image/png" />
	<link rel="SHORTCUT ICON" href="favicon.ico" />
	<link rev="made" href="mailto:elric@planetblood.com" />
	<style type="text/css">
	<!--
		body {
			background: #505050;
			color: #000000;
			padding: 10px;
			text-align: justify;
		}

		a:link { color: #3661a1; }
		a:visited { color: #6f6c81; }
		a:active { color: #d5ae83; }

		div.cvs-module-name {
			font-style: italic;
			text-align: center;
		}
		div.section {
			padding: 10px;
			text-align: justify;
		}

		h1.title {
			background: #ffffff;
			color: #800000;
			text-decoration: underline;
		}
		h2.section {
			font-weight: bold;
			text-align: center;
			text-decoration: underline;
		}

		span.boldtitle {
			font-weight: bold;
			text-decoration: underline;
		}
		span.title { text-decoration: underline; }
		span.footnotes-title { font-weight: bold; }

		table {
			background: #ffffff;
			border-spacing: 0;
			color: #000000;
 			width: 100%;
 		}
		td.separator {
			background: #505050;
			height: 3px;
		}
		td.links {
			background: #d9ddf5;
			height: 20px;
			text-align: center;
		}
    -->
	</style>
	<?php
	echo ("	<title>The Transfusion Project - " . $page_title . "</title>\n");
	?>
</head>

<body>
	<table>
		<tr valign="top">
			<td align="center" valign="middle">
				<a href="images/scr_win32.jpg">
					<img src="images/min_scr_win32.jpg" alt="Transfusion on Win32" />
				</a>
			</td>
			<td align="center" valign="middle">
				<?php
				echo ("				<h1 class=\"title\">" . $page_topic . "</h1>\n");
				if ($page_cvs)
				{
					echo ("<div class=\"cvs-module-name\">CVS module name: ");
					ViewCvsURL ($page_cvs, $page_cvs);
					echo ("</div><br />\n");
				}
				?>
			</td>
			<td align="center" valign="middle">
				<a href="images/scr_linux.jpg">
					<img src="images/min_scr_linux.jpg" alt="Transfusion on Linux" />
				</a>
			</td>
		</tr>
	</table>

	<!-- **************************************************************** -->

	<table border="0">
		<tr><td class="separator"></td></tr>

		<tr valign="middle">
			<td class="links">
				<b>
				<a  href="index.php">Home</a>
				&nbsp;::&nbsp;
				<a href="transfusion.php">Transfusion</a>
				&nbsp;::&nbsp;
				<a href="awakening.php">Transfusion II: Caleb's Awakening</a>
				&nbsp;::&nbsp;
				<a href="rebuild.php">ReBUILD</a>
				&nbsp;::&nbsp;
				<a href="http://sourceforge.net/project/showfiles.php?group_id=22136">Files</a>
				&nbsp;::&nbsp;
				<a href="snapshots.php">Snapshots</a>
				</b>
			</td>
		</tr>

		<tr><td class="separator"></td></tr>

		<tr valign="middle">
			<td class="links">
				<b>
				<?php
					$nb_links = 0;
					while (list ($link_name, $link_props) = each ($page_links)) {
						if ($nb_links)
							echo ("				&nbsp;::&nbsp;\n");
						$nb_links++;

						echo ("<a href=\"" . $page_links[$link_name]["Address"] . "\">" . $page_links[$link_name]["Text"] . "</a>\n");
					}

				?>
				</b>
			</td>
		</tr>

		<tr><td class="separator"></td></tr>
	</table>

	<!-- **************************************************************** -->

	<table>
		<tr valign="top">
			<td align="left">