<?php
    //KẾT NỐI MYSQL SERVER
   
    $dbusername = "tranc147_luan172";  
    $dbpassword = "Luan123";  
    $server = "mysql06.dotvndns.vn"; 

    // KẾT NỐI DATABASE

    $dbconnect = mysqli_connect($server, $dbusername, $dbpassword);
    $dbselect = mysqli_select_db($dbconnect, "tranc147_data1");

    // QUERY XỬ LÝ DỮ LIỆU

    $sql = "INSERT INTO tranc147_data1.congsuat (value) VALUES ('".$_GET["value"]."')";    
    mysqli_query($dbconnect, $sql);

?>