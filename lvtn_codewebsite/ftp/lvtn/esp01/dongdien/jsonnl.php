<?php
   
    $con=mysqli_connect("mysql06.dotvndns.vn","tranc147_luan172","Luan123","tranc147_data1");
       
    // Retrieve all records and display them   
    $now = date("Y-m-d 23:59:59");
    $now1 = strtotime($now);
    $now2 = date("Y-m-d 0:0:0");
    //$now3 = strtotime($now2);
   //$result = mysqli_query($con,'SELECT value,Timestamp FROM congsuat1 ORDER BY id DESC LIMIT 50');
    $result = mysqli_query($con,"SELECT * FROM nangluong where Timestamp <= '$now' and Timestamp >= '$now2' and (MINUTE(Timestamp) = 0 or MINUTE(Timestamp) = 15 or MINUTE(Timestamp) = 30 or MINUTE(Timestamp) = 45)and second(timestamp)<=10" );
    $data = [];
    while($row = mysqli_fetch_array($result))
    {
       
       array_push($data, array(
        'period'=>strval($row['Timestamp']),
        'nangluong'=>round(floatval($row['value']),2)
        ));
    }
    // Process every record
    echo json_encode($data);    
        
    mysqli_free_result($result);
    // Close the connection   
    mysqli_close($con);
?>