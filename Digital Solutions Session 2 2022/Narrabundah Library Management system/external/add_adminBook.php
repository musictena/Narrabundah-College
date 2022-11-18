<html>

<head>
	<meta charset="UTF-8">
	<meta http-equiv="X-UA-Compatiable" content="IE-edge">
	<meta name="author" content="Phebe Le">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<meta name="description" content="library, catalogue, student">

	<title>Add Book</title>

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

	if(isset($_POST['add_book']))
	{
		$book_title = @$_POST['book_title'];
		$book_type = @$_POST['book_type'];
		$book_author = @$_POST['book_author'];
		$book_year = @$_POST['book_year'];
		$book_avaliability = @$_POST['book_avaliability'];

		$check="SELECT * FROM book WHERE book_title='$book_title' ";
		$check_booktitle=mysqli_query($dbc,$check);
		$row_count=mysqli_num_rows($check_booktitle);
		if($row_count==1)
		{
			$_SESSION['message']='Book Title already exist, please edit Title';
		} else
		{
			$sql = "INSERT into $tablename (book_title, book_type, book_author, book_year, book_avaliability ) 
						values ( \"$book_title\", \"$book_type\", \"$book_author\", \"$book_year\", \"$book_avaliability\")";
			#execute the query
			$result = @mysqli_query($dbc, $sql);
			
			if (!$result) 
			{
				$_SESSION['message']='Record add failed.';
			} else {
				$_SESSION['message']='Record added successfully.';
			}
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
				<a title="Admin Profile" href="../external/profile.php"><img src="../internal/images/adminpic.png"></a>
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

		<!-- Add book form -->
		<section id="addUser">
			<form action="<?php echo ($self); ?>" method="post">
				<div>
					<div>
						<h3>Add Book</h3>
						<div class="form-group">
							<label for="book_title">Book Title</label><br>
							<input type="text" name="book_title" class="form-control" require value='' >
						</div>
						<div class="form-group">
							<label for="book_type">Book Genre</label><br>
							<input type="text" name="book_type" class="form-control" value='' >
						</div>
						<div class="form-group">
							<label for="book_author">Book Author</label><br>
							<input type="text" name="book_author" class="form-control" value='' >
						</div>
						<div class="form-group">
							<label for="book_year">Date of publication</label><br>
							<input type="date" name="book_year" class="form-control" value='' >
						</div>
						<div class="form-group">
							<label for="book_avaliability">Book Avaliability</label><br>
							<input type="text" name="book_avaliability" class="form-control" value='' >
						</div>
					</div>
					<div class="form-footer">
						<input type="submit" class="btn btn-success" name="add_book" value="Add book">
					</div>
				</div>
			</form>
		</section>
	</section>
</body>

</html>