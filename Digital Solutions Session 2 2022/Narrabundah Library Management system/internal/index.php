<?php

// echo "I am about to authenticate";
     
    require('../internal/connection.php');  
    $userid = $_POST['userid'];  
    $password = $_POST['password'];  

   
    // echo "this is the value for user id : $userid";
    // echo "this is the value for password : $password";
      
        //to prevent from mysqli injection  
        $userid = stripcslashes($userid);  
        $password = stripcslashes($password);  
        $userid = mysqli_real_escape_string($con, $userid);  
        $password = mysqli_real_escape_string($con, $password);  
      
        $sql = "select *from user where user_id = '$userid' and user_password = '$password'";  
        $result = mysqli_query($con, $sql);  
        $row = mysqli_fetch_array($result, MYSQLI_ASSOC);  
        // echo '<pre>'; print_r($row); echo '</pre>';
        $count = mysqli_num_rows($result);  

        if($count == 1){  
            // echo "<h1><center> Login successful </center></h1>";  
            if ($row['user_type'] == 'admin')  {
                header('Location: ../external/index_interface.php');
                // require('../external/index_interface.php');
            } else if ($row['user_type'] == 'student')  {
                require('../external/index_student.php');
            } else {
                echo "<h1><center> Login successful but unknown type </center></h1>";           
            };
        }  
        else{  
            echo "<h1> Login failed. Invalid user id or password.</h1>";  
        }     
 
        
?> 