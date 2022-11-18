<html>

<head>
	<meta charset="UTF-8">
	<meta http-equiv="X-UA-Compatiable" content="IE-edge">
	<meta name="author" content="Phebe Le">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<meta name="description" content="library, catalogue, student">

	<title>Borrow book</title>

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
	$tablename = "borrow";

	if(isset($_POST['add_borrow']))
	{
        $trans_id = @$_POST['trans_id'];
        $trans_date = @$_POST['trans_date'];
		$borrow_userid = @$_POST['borrow_userid'];
		$borrow_bookid = @$_POST['borrow_bookid'];
		$trans_expiry = @$_POST['trans_expiry'];

		$check="SELECT * FROM borrow WHERE trans_id='$trans_id' ";
		$check_transid=mysqli_query($dbc,$check);
		$row_count=mysqli_num_rows($check_transid);
		if($row_count==1)
		{
			$_SESSION['message']='Transaction id already exist, please edit ID';
		} else
		{
			$sql = "INSERT into $tablename (trans_id, trans_date, borrow_userid, borrow_bookid, trans_expiry) 
						values ( \"$trans_id\", \"$trans_date\", \"$borrow_userid\", \"$borrow_bookid\", \"$trans_expiry\")";
			#execute the query
			$result = @mysqli_query($dbc, $sql);
			
			if (!$result) 
			{
				$_SESSION['message']='Book borrowing failed.';
			} else {
				$_SESSION['message']='Book borrowed successfully. Enjoy your read.';
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
            <li><i class="fa-solid fa-house"></i><a href="../external/index_student.php" title="Main Dashboard">Dashboard</a></li>
            <li><i class="fa-solid fa-book-open-reader"></i><a href="../external/student_book.php" title="Library Catalogue">Library Catalogue</a></li>
            <li><i class="fa-solid fa-book-open-reader"></i><a href="../external/student_borrow.php" title="Borrow">Borrow</a></li>
            <li><i class="fa-solid fa-right-from-bracket"></i><a title="Logout" href="../external/sign_in.php">Logout</a></li>
            <br>
        </div>
    </section>
    <section id="interface">
        <div class="banner">
            <img src="../internal/images/banner.jpg" alt="banner">
        </div>
        <div class="navigation">
            <form name="searchFrm" method="post" action="<?php echo $self ?> ">
                <div class="search">
                    <i class="fa-solid fa-magnifying-glass"></i>
                    <input type="text" name="valueToSearch" placeholder="Enter text to search"> <br>
                    <input type="submit" class="btn btn-success" name="search" value="Filter">

                </div>
            </form>
            <div class="profile">
                <i class="fa-solid fa-user"> Hello Student <?php print($user); ?></i>
                <a title="Logout" href="../external/sign_in.php"><img src="../internal/images/hatori.png"></a>
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

		<!-- Add Borrow form -->
		<section id="addUser">
			<form action="<?php echo ($self); ?>" method="post">
				<div>
					<div>
						<h3>Borrow</h3>
						<div class="form-group">
							<label for="trans_id">Transaction ID</label><br>
							<input type="text" name="trans_id" class="form-control" require value='' >
						</div>
						<div class="form-group">
							<label for="trans_date">Transaction Date</label><br>
							<input type="date" name="trans_date" class="form-control" value='' >
						</div>
						<div class="form-group">
							<label for="borrow_userid">Borrower ID</label><br>
							<input type="text" name="borrow_userid" class="form-control" value='' >
						</div>
						<div class="form-group">
							<label for="borrow_bookid">Book ID</label><br>
							<input type="text" name="borrow_bookid" class="form-control" value='' >
						</div>
						<div class="form-group">
							<label for="trans_expiry">Book Expiry Date</label><br>
							<input type="date"  name="borrow_bookid" class="form-control" value='' >
						</div>
					</div>
					<div class="form-footer">
						<input type="submit" class="btn btn-success" name="add_borrow" value="Borrow">
					</div>
				</div>
			</form>
		</section>
	</section>
</body>

</html>