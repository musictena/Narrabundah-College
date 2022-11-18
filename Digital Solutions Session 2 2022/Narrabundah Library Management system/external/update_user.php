<html>

<head>
	<meta charset="UTF-8">
	<meta http-equiv="X-UA-Compatiable" content="IE-edge">
	<meta name="author" content="Phebe Le">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<meta name="description" content="library, catalogue, student">

	<title>Update User</title>

	<script src="https://kit.fontawesome.com/a945d9a40f.js"></script>
	<script src="https://code.jquery.com/jquery-1.10.2.js"></script>
	<script src="https://code.jquery.com/ui/1.10.4/jquery-ui.js"></script>
	<script type="text/javascript" src="../internal/jQuery/jQuery.js"></script>
	<link rel="stylesheet" type="text/css" href="../internal/styleSheet/style.css">
	<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.0/css/bootstrap.min.css">

</head>
<?php 
   	error_reporting(0);
    session_start();

	# CONNECT TO MySQL DATABASE.
	# Otherwise fail gracefully and explain the error.
	$dbc = @mysqli_connect('localhost', 'admin', 'admin', 'narcollege')
		or die(mysqli_connect_error());

	# Set encoding to match PHP script encoding.
	mysqli_set_charset($dbc, 'utf8');

	$self = $_SERVER['PHP_SELF'];
	$tablename = "user";

	if($_GET['update_userid'])
	{
		$update_userid=$_GET['update_userid'];
		$update_sql="SELECT * FROM user WHERE user_id='$update_userid' ";
		$update_data=mysqli_query($dbc,$update_sql);
		$row = mysqli_fetch_array($update_data, MYSQLI_ASSOC);  
        // echo '<pre>'; print_r($row); echo '</pre>';	
	}


	if(isset($_POST['update_user']))
	{
		$user_id = @$_POST['user_id'];
		$user_name = @$_POST['user_name'];
		$user_type = "student";
		$user_password = @$_POST['user_password'];
		$user_email = @$_POST['user_email'];
		$user_enrol_date = @$_POST['user_enrol_date'];

		$sql = "UPDATE `user` SET `user_name`='$user_name',`user_type`='$user_type',`user_email`='$user_email',`user_password`='$user_password',`user_enrol_date`='$user_enrol_date'  WHERE `user_id`='$user_id' ";

		#execute the query
		$result = @mysqli_query($dbc, $sql);
		
		if (!$result) 
		{
			$_SESSION['message']='Record update failed.';
		} else {
			$_SESSION['message']='Record update successfully.';
			
			header("Location:index_interface.php");

		}
	}

?>

<body class="dashboard">

	<section id="menu">
		<div class="logo">
			<img src="../internal/images/narrabundahlogo.jpg" alt="Narrabundah Logo">
			<h3>Narrabundah Library Database</h3>
		</div>
		<div class=" items">
			<li><i class="fa-solid fa-house"></i><a title="Dashboard" href="../external/index_interface.php">Dashboard</a></li>
			<li><i class="fa-solid fa-book-open-reader"></i><a title="Library Catalogue" href="../external/admin_book.php">Library Catalogue</a></li>
			<li><i class="fa-solid fa-user-plus"></i><a href="../external/add_user.php" title="Add User">Add User</a></li>            
			<li><i class="fa-solid fa-square-plus"></i><a title="Add Book" href="../external/add_adminBook.php">Add Books</a></li>
			<li><i class="fa-solid fa-book-open-reader"></i><a href="../external/admin_borrow.php" title="Borrow">Borrow</a></li>
			<li><i class="fa-solid fa-right-from-bracket"></i><a title="Logout" href="../external/sign_in.php">Logout</a></li>
			<br>
		</div>
	</section>
	<section id="interface">
		<div class="banner">
			<img src="../internal/images/banner.jpg" alt="banner">
		</div>
		<div class="navigation">
			<div class="time">
				<i class="fa-solid fa-calendar-day"></i><?php echo " " . date("d/m/y") . "<br>"; ?>
            </div>
			<div class="profile">
				<i class="fa-solid fa-user"> Hello Admin </i>
				<a title="Logout" href="../external/profile.php"><img src="../internal/images/adminpic.png" ></a>
				
			</div>

		</div>
		<!-- Display error message -->
		<div>
			<?php
				if($_SESSION['message'])
				{
					echo $_SESSION['message'];
				}

				unset($_SESSION['message']);
				
			?>
		</div>

		<!-- Update user form -->
		<section id="addUser">
			<form action="<?php echo ($self); ?>" method="post">
				<div >
					<div >
						<h3>Update User</h3>
						<div class="form-group">
							<label for="user_id">User Id</label><br>
							<input type="text" name="user_id" class="form-control" require value='<?php echo $row["user_id"]; ?>'>
						</div>
						<div class="form-group">
							<label for="user_name">User Name</label> <br>
							<input type="text" name="user_name" class="form-control" value='<?php echo $row["user_name"]; ?>' >
						</div>
						<div class="form-group">
							<label for="user_password">User Password</label><br>
							<input type="text" name="user_password" class="form-control" value='<?php echo $row["user_password"]; ?>'  >
						</div>
						<div class="form-group">
							<label for="user_email">User Email</label><br>
							<input type="email" name="user_email" class="form-control" value='<?php echo $row["user_email"]; ?>' >
						</div>
						<div class="form-group">
							<label for="user_enrol_date">User Enrol Date</label><br>
							<input type="date" id="user_enrol_date" name="user_enrol_date" class="form-control" value='<?php echo $row["user_enrol_date"]; ?>' >
						</div>						
					</div>
					<div class="form-footer">
						<input type="submit" class="btn btn-success" name="update_user" value="Update user">
					</div>
				</div>
			</form>
		</section>
	</section>
	
</body>

</html>