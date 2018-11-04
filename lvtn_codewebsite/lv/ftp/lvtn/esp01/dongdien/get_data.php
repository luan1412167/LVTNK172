<?php
$url=$_SERVER['REQUEST_URI'];
header("Refresh: 60; URL=$url");  // Refresh the webpage every 20 seconds
?>
<html>
<head>
    <title>Dongdien</title>
</head>
    <body>
        <h1>Dong dien readings</h1>
    <table border="0" cellspacing="0" cellpadding="4">
      <tr>
            <td>ID</td>
            <td>Timestamp</td>
            <td>Value</td>
      </tr>
      
<?php
    // Connect to database

   // IMPORTANT: If you are using XAMPP you will have to enter your computer IP address here, if you are using webpage enter webpage address (ie. "www.yourwebpage.com")
    $con=mysqli_connect("mysql06.dotvndns.vn","tranc147_luan172","Luan123","tranc147_data1");
       
    // Retrieve all records and display them   
    $result = mysqli_query($con,'SELECT * FROM dongdien ORDER BY id DESC');
      
    // Process every record
    
    while($row = mysqli_fetch_array($result))
    {      
        echo "<tr>";
        echo "<td>" . $row['id'] . "</td>";
        echo "<td>" . $row['time'] . "</td>";
        echo "<td>" . $row['value'] . "</td>";
        echo "</tr>";
        
    }
        
    // Close the connection   
    mysqli_close($con);
?>
    </table>
    </body>
</html>