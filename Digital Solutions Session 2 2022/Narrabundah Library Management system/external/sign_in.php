<?php
require "../internal/connection.php"
?>

<html>  
<head>  
    <title>PHP login system</title>  
    <meta charset = "utf-8">
      <link href = "https://code.jquery.com/ui/1.10.4/themes/ui-lightness/jquery-ui.css"
         rel = "stylesheet">
    <link rel = "stylesheet" type = "text/css" href = "../internal/styleSheet/style.css">   
</head>  
<body>  
    <div id = "frm">  
        <h1>Login</h1> 
        <h3><i class="fa-solid fa-calendar-day"></i><?php echo "Today's date is " . date("d/m/y") . "<br>"; ?></h3>
        <form name="f1" action = "../internal/index.php" onsubmit = "return validation()" method = "POST">  
            <p>  
                <label> User ID: </label>  
                <input type = "text" placeholder="Enter User ID" id ="userid" name  = "userid" required />  
            </p>  
            <p>  
                <label> Password: </label>  
                <input type = "password" placeholder="Enter Password " id ="password" name  = "password" required/> 
            </p>  
            <p>     
                <input type =  "submit" id = "sbtn" value = "Login" />  
            </p>  
            <p>
                <span class="psw">Forgot <a id="tooltip-1" href="" title="Please contact us">password?</a></span>
            </p>   
        </form>
    </div>  
   
    <script>  
    // this function is validating input user id and user password
        function validation()  
        {  
            var userid=document.f1.userid.value;  
            var password=document.f1.password.value; 
            // alert (userid);
            // alert (password);
            if(userid.length=="" && password.length=="") {  
                alert("Username and Password fields are empty");  
                return false;  
            }  
            else  
            {  
                if(userid.length=="") {  
                    alert("User ID is empty");  
                    return false;  
                }   
                if (password.length=="") {  
                alert("Password field is empty");  
                return false;  
                }  
            }                             
        }  
        
    </script>  
</body>     
</html>  
