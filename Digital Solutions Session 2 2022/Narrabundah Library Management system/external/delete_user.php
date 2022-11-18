
<?php
session_start();
$host = "localhost";  
$username = "admin";  
$password = "admin"; 
$db_name = "narcollege";   
  
  
$data = mysqli_connect($host, $username, $password, $db_name); 

if($_GET['delete_user'])
{

    $delete_user=$_GET['delete_user'];
    //DELETE QUERY
    $sql="DELETE FROM `user` WHERE `user`.`user_number`='$delete_user' ";
    $result=mysqli_query($data,$sql);
    if ($result)
    {
        $_SESSION['message']='Delete user is Successful';
        header("location:index_interface.php");
    }

}






?>