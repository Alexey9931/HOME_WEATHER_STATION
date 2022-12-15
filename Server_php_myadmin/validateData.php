<?php

require "conn.php";
$id = $_POST["id"];
//$user_name = "shah";
//$password = "1234";

$mysqli_query = "SELECT * FROM HomeWeatherStationIvnya where id like '$id'";

$result = mysqli_query($conn,$mysqli_query);

if(mysqli_num_rows($result)>0){
//print("Login success");
$row = mysqli_fetch_assoc($result); 
$HomeTemp =$row["HomeTemp"]; 
$StreetTemp =$row["StreetTemp"];
$HomeHum =$row["HomeHum"];
$StreetHum =$row["StreetHum"];
$Pressuare =$row["Pressuare"];
$WindSpeed =$row["WindSpeed"];
$WindDirect =$row["WindDirect"];
$Rain =$row["Rain"];
$BatteryCharge =$row["BatteryCharge"];
$MeasureTime =$row["MeasureTime"];
Print($HomeTemp."|".$StreetTemp."|".$HomeHum."|".$StreetHum."|".$Pressuare."|".$WindSpeed."|".$WindDirect."|".$Rain."|".$BatteryCharge."|".$MeasureTime."|");

}
else{
print("Empty id"); 
}

?>