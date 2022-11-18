<html>

<head>
	<meta charset="UTF-8">
	<meta http-equiv="X-UA-Compatiable" content="IE-edge">
	<meta name="author" content="Phebe Le">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<meta name="description" content="library, catalogue, student">

	<title>Update Book</title>

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
	$tablename = "book";

	if($_GET['update_bookid'])
	{
		$update_bookid=$_GET['update_bookid'];
		$update_sql="SELECT * FROM book WHERE book_id='$update_bookid' ";
		$update_data=mysqli_query($dbc,$update_sql);
		$row = mysqli_fetch_array($update_data, MYSQLI_ASSOC);
        // echo '<pre>'; print_r($row); echo '</pre>';
	}


	if(isset($_POST['update_book']))
	{
		$book_id = @$_POST['book_id']; // hidden input for update
		$book_title = @$_POST['book_title'];
		$book_type = @$_POST['book_type'];
		$book_author = @$_POST['book_author'];
		$book_year = @$_POST['book_year'];
		$book_avaliability = @$_POST['book_avaliability'];

		$sql = "UPDATE `book` SET `book_title`='$book_title',`book_type`='$book_type',`book_author`='$book_author',`book_year`='$book_year',`book_avaliability`='$book_avaliability' WHERE `book_id`=$book_id ";
		#execute the query
		$result = @mysqli_query($dbc, $sql);
		
		if (!$result)
		{
			$_SESSION['message']='Record update failed.';
		} else {
			$_SESSION['message']='Record update successfully.';
			// header("Location:update_book.php");
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
				<i class="fa-solid fa-user"> Hello Admin</i>
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

		<!-- Update book form -->
		<section id="addUser">
			<form action="<?php echo ($self); ?>" method="post">
				<div>
					<div>
						<h3>Update Book</h3>
						<div class="form-group">
							<label for="book_title">Book Name</label><br>
							<input type="text" name="book_title" class="form-control" value='<?php echo $row["book_title"]; ?>'  >
						</div>
						<div class="form-group">
							<label for="book_type">Book Genre</label><br>
							<input type="text" name="book_type" class="form-control" value='<?php echo $row["book_type"]; ?>'  >
						</div>
						<div class="form-group">
							<label for="book_author">Book Author</label><br>
							<input type="text" name="book_author" class="form-control" value='<?php echo $row["book_author"]; ?>' >
						</div>
						<div class="form-group">
							<label for="book_year">Date of Publication</label><br>
							<input type="date" id="book_year" name="book_year" class="form-control" value='<?php echo $row["book_year"]; ?>' >
						</div>
						<div class="form-group">
							<label for="book_avaliability">Book Avaliability</label><br>
							<input type="text" id="book_avaliability" name="book_avaliability" class="form-control" value='<?php echo $row["book_avaliability"]; ?>' >
						</div>
					</div>
					<div class="form-footer">
					    <input type="hidden" name="book_id" class="form-control" value='<?php echo $row["book_id"]; ?>'  >
						<input type="submit" class="btn btn-success" name="update_book" value="Update book">
					</div>
				</div>
			</form>
		</section>
	</section>
	
</body>

</html>