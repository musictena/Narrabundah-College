<html>

<head>
	<meta charset="UTF-8">
	<meta http-equiv="X-UA-Compatiable" content="IE-edge">
	<meta name="author" content="Phebe Le">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<meta name="description" content="library, catalogue, student"> 

	<title>Admin Profile</title>

	<script src="https://kit.fontawesome.com/a945d9a40f.js"></script>
	<script src="https://code.jquery.com/jquery-1.10.2.js"></script>
	<script src="https://code.jquery.com/ui/1.10.4/jquery-ui.js"></script>
	<script type="text/javascript" src="../internal/jQuery/jQuery.js"></script>
    <link href = "https://code.jquery.com/ui/1.10.4/themes/ui-lightness/jquery-ui.css"
         rel = "stylesheet">
	<link rel="stylesheet" type="text/css" href="../internal/styleSheet/style.css">
	<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.0/css/bootstrap.min.css">

</head>
<?php
    // set error handling
    error_reporting(0);
    // Initalise session data
    session_start();

    // find book count 
    $query = "SELECT * FROM book ";
    $result = filterTable($query);
    $numBook = mysqli_num_rows($result);

	$query = "SELECT * FROM borrow ";
    $result = filterTable($query);
    $numBorrow = mysqli_num_rows($result);

    if (isset($_POST['search'])) {
        $valueToSearch = $_POST['valueToSearch'];
        $query = "SELECT * FROM user WHERE CONCAT(user_id, user_name, user_type, user_email, user_password, user_enrol_date) LIKE '%" . $valueToSearch . "%' ";
        $result = filterTable($query);
        $numUser = mysqli_num_rows($result);
    } else if(isset($_POST['sortUserName'])) {
        $query = "SELECT * FROM user ORDER BY `user_name` ASC ";
        $result = filterTable($query);
        $numUser = mysqli_num_rows($result);
    } else if(isset($_POST['sortUserEmail'])) {
        $query = "SELECT * FROM user ORDER BY `user_email` ASC ";
        $result = filterTable($query);
        $numUser = mysqli_num_rows($result);        
    } else {
        $query = "SELECT * FROM user ORDER BY `user_number` ASC ";
        $result = filterTable($query);
        $numUser = mysqli_num_rows($result);
    }


    function filterTable($query)
    {
        $con = @mysqli_connect('localhost', 'admin', 'admin', 'narcollege')
            or die(mysqli_connect_error());
        $filer_result = @mysqli_query($con, $query);
        return $filer_result;
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
			<div id = "progressbar-5">
				<div class = "progress-label">
					Loading...
				</div>
			</div>
		</div>
        <h3 class="i-name">Admin Profile</h3>
        <div class="values">
            <div class="val-box">
			<a href="index_interface.php"><i class="fa-solid fa-users"></i></a>
                <div>
                    <h3>
                        <?php
                        printf($numUser);
                        ?>
                    </h3>
                    <span>Users</span>
                </div>
            </div>
            <div class="val-box">
			<a href="admin_book.php"><i class="fa-solid fa-book"></i></a>
                <div>
                    <h3>
                    	<?php
                        printf($numBook);
                        ?>
                    </h3>
                    <span>Books</span>
                </div>
            </div>
            <div class="val-box">
                <div id = "box-1"><i class="fa-solid fa-address-book"></i></div>
                <div>
                    <h3>
						<?php
                        printf($numBorrow);
                        ?>
					</h3>
                    <span>Borrowed books</span>
                </div>
            </div>
            <div class="val-box">
			<div id = "box-2"><i class="fa-solid fa-calendar-day"></i></div>
			<div>
                    <h3>Date:</h3>
                    <span>
						<?php
							echo "" . date("d/m/y") . "<br>";
						?>
                    </span>
                </div>
            </div>
        </div>
		<br>


		<!-- Admin User information form -->
		<section id="addUser">
			<form action="" method="post">
				<div >
					<div id="accordion-1" >
						<h3 style="color:#1C94C4; border: 1px solid #cccccc;">Admin ID</h3>
						<div class="form-group">
							<label for="user_id">Admin Id</label><br>
							<input type="text" name="user_id" class="form-control" require value='aaa'>
						</div>
                        <h3 style="color:#1C94C4; border: 1px solid #cccccc;">Admin Name</h3>
						<div class="form-group">
							<label for="user_name">Admin Name</label> <br>
							<input type="text" name="user_name" class="form-control" value='admin' >
						</div>
                        <h3 style="color:#1C94C4; border: 1px solid #cccccc;">Admin Password</h3>
						<div class="form-group">
							<label for="user_password">Admin Password</label><br>
							<input type="text" name="user_password" class="form-control" value='222'  >
						</div>
                        <h3 style="color:#1C94C4; border: 1px solid #cccccc;">Admin Password</h3>
						<div class="form-group">
							<label for="user_email">Admin Email</label><br>
							<input type="email" name="user_email" class="form-control" value='admin@gmail.com' >
						</div>
                        <h3 style="color:#1C94C4; border: 1px solid #cccccc;">Admin Creation Date</h3>
						<div class="form-group">
							<label for="user_enrol_date">Admin Enrol Date</label><br>
							<input type="text" id="user_enrol_date" name="user_enrol_date" class="form-control" value='11/11/2005' >
						</div>						
					</div>
				</div>
			</form>
		</section>
	</section>
	
</body>

</html>