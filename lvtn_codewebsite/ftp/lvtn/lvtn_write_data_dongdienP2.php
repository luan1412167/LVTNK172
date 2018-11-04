<?php

    // Prepare variables for database connection
   
    $dbusername = "tranc147_luan172";  
    $dbpassword = "Luan123";  
    $server = "mysql06.dotvndns.vn"; 

    // Connect to your database

    $dbconnect = mysqli_connect($server, $dbusername, $dbpassword);
    $dbselect = mysqli_select_db($dbconnect, "tranc147_data1");

    // Prepare the SQL statement

    $sql = "INSERT INTO tranc147_data1.dongdien1 (value) VALUES ('".$_GET["value"]."')";    

    // Execute SQL statement

    mysqli_query($dbconnect, $sql);

?>