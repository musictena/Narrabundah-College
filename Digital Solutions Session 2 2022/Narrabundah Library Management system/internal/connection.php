<?php
 $host = "localhost";  
 $username = "admin";  
 $password = "admin"; 
 $db_name = "narcollege";   
   
   
 $con = mysqli_connect($host, $username, $password, $db_name);  
 if(mysqli_connect_error()) {  
    // otherwise fail and explain error
     die("Failed to connect with MySQL: ". mysqli_connect_error());  
 }  

?>  