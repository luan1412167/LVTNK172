<?php
    $connect = function connect ()
    {
	$dbusername = "tranc147_luan172";  
    $dbpassword = "Luan123";  
    $server = "mysql06.dotvndns.vn"; 
    $db1connect = mysqli_connect($server, $dbusername, $dbpassword);
    return $db1connect;
    }
    $disconnect=function disconnect()
    {
    	$dis1connect =mysql_close($dbconnect);
    	return $dis1connect; 
    }
?>

   
    
    