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

// Keep this API Key value to be compatible with the ESP32 code provided in the project page. 
// If you change this value, the ESP32 sketch needs to match
$api_key_value = "tPmAT5Ab3j7F9";

$api_key= $id = $HomeTemp = $StreetTemp = $HomeHum = $StreetHum = $Pressuare = $WindSpeed = $WindDirect = $Rain = $BatteryCharge = $Time = $MeasureTime = "";

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $api_key = test_input($_POST["api_key"]);
    if($api_key == $api_key_value) {
        $id = test_input($_POST["id"]);
        $HomeTemp = test_input($_POST["HomeTemp"]);
        $StreetTemp = test_input($_POST["StreetTemp"]);
        $HomeHum = test_input($_POST["HomeHum"]);
        $StreetHum = test_input($_POST["StreetHum"]);
        $Pressuare = test_input($_POST["Pressuare"]);
        $WindSpeed = test_input($_POST["WindSpeed"]);
        $WindDirect = test_input($_POST["WindDirect"]);
        $Rain = test_input($_POST["Rain"]);
        $BatteryCharge = test_input($_POST["BatteryCharge"]);
        $reading_time = test_input($_POST["reading_time"]);
        $MeasureTime = test_input($_POST["MeasureTime"]);
        
        // Create connection
        $conn = new mysqli($servername, $username, $password, $dbname);
        // Check connection
        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
        } 
        
        $sql = "INSERT INTO HomeWeatherStationIvnya (id, HomeTemp, StreetTemp, HomeHum, StreetHum, Pressuare, WindSpeed, WindDirect, Rain, BatteryCharge, reading_time, MeasureTime)
        VALUES ('" . $id . "', '" . $HomeTemp . "', '" . $StreetTemp . "', '" . $HomeHum . "', '" . $StreetHum . "', '" . $Pressuare . "', '" . $WindSpeed . "', '" . $WindDirect . "', '" . $Rain . "', '" . $BatteryCharge . "','" . $reading_time . "', '" . $MeasureTime . "')";
        
        if ($conn->query($sql) === TRUE) {
            echo "New record created successfully";
        } 
        else {
            echo "Error: " . $sql . "<br>" . $conn->error;
        }
    
        $conn->close();
    }
    else {
        echo "Wrong API Key provided.";
    }

}
else {
    echo "No data posted with HTTP POST.";
}

function test_input($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}