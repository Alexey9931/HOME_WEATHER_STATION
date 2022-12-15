<!DOCTYPE html>
<html>
<head>
   <link rel="stylesheet" href="css" />
</head>    
<body>
<?php
/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-esp8266-mysql-database-php/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

$servername = "localhost";

// REPLACE with your Database name
$dbname = "esp_data";
// REPLACE with Database user
$username = "alexey";
// REPLACE with Database user password
$password = "alex281299";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$sql = "SELECT id, HomeTemp, StreetTemp, HomeHum, StreetHum, Pressuare, WindSpeed, WindDirect, Rain, BatteryCharge, reading_time, MeasureTime FROM HomeWeatherStationIvnya ORDER BY id DESC";

echo '<p style="font-style:inherit" align=center><font size="5" color="blue" face="Arial">БАЗА ДАННЫХ с результатами измерений проекта HomeWeatherStation</p>';
echo '<table cellspacing="5" cellpadding="5" align=center>
      <tr> 
        <td>№</td> 
        <td>Дом.темп.</td> 
        <td>Ул.темп.</td> 
        <td>Дом.влажность</td> 
        <td>Ул.влажность</td>
        <td>Давление</td> 
        <td>Скорость ветра</td> 
        <td>Направление ветра</td> 
        <td>Осадки</td> 
        <td>Заряд батареи</td> 
        <td>Время получения сервером</td> 
        <td>Время измерения</td>
      </tr>';
 
if ($result = $conn->query($sql)) {
    while ($row = $result->fetch_assoc()) {
        $row_id = $row["id"];
        $row_HomeTemp = $row["HomeTemp"];
        $row_StreetTemp = $row["StreetTemp"];
        $row_HomeHum = $row["HomeHum"];
        $row_StreetHum = $row["StreetHum"]; 
        $row_Pressuare = $row["Pressuare"]; 
        $row_WindSpeed = $row["WindSpeed"];
        $row_WindDirect = $row["WindDirect"];
        $row_Rain = $row["Rain"];
        $row_BatteryCharge = $row["BatteryCharge"];
        $row_reading_time = $row["reading_time"];
        $row_MeasureTime = $row["MeasureTime"];
        // Uncomment to set timezone to - 1 hour (you can change 1 to any number)
        //$row_reading_time = date("Y-m-d H:i:s", strtotime("$row_reading_time - 1 hours"));
      
        // Uncomment to set timezone to + 4 hours (you can change 4 to any number)
        //$row_reading_time = date("Y-m-d H:i:s", strtotime("$row_reading_time + 4 hours"));
      
        echo '<tr> 
                <td>' . $row_id . '</td> 
                <td>' . $row_HomeTemp . '</td> 
                <td>' . $row_StreetTemp . '</td> 
                <td>' . $row_HomeHum . '</td> 
                <td>' . $row_StreetHum . '</td>
                <td>' . $row_Pressuare . '</td> 
                <td>' . $row_WindSpeed . '</td> 
                <td>' . $row_WindDirect . '</td> 
                <td>' . $row_Rain . '</td> 
                <td>' . $row_BatteryCharge . '</td> 
                <td>' . $row_reading_time . '</td> 
                <td>' . $row_MeasureTime . '</td>
              </tr>';
    }
    $result->free();
}

$conn->close();
?> 
</table>
</body>
</html>