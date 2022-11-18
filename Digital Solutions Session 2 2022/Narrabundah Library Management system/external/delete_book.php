<?php
session_start();
$host = "localhost";  
$username = "admin";  
$password = "admin"; 
$db_name = "narcollege";   
  
  
$data = mysqli_connect($host, $username, $password, $db_name); 

if($_GET['delete_bookid'])
{

    $delete_bookid=$_GET['delete_bookid'];
    //DELETE QUERY
    $sql="DELETE FROM `book` WHERE `book`.`book_id`='$delete_bookid' ";
    $result=mysqli_query($data,$sql);
    if ($result)
    {
        $_SESSION['message']='Delete book is Successful';
        header("location:admin_book.php");
    }

}






?>