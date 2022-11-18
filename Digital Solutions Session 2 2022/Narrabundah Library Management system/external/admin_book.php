<html>

<head>
    <meta charset="UTF-8">
	<meta http-equiv="X-UA-Compatiable" content="IE-edge">
	<meta name="author" content="Phebe Le">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<meta name="description" content="library, catalogue, student">

    <title>Library Catalogue</title>

    <script src="https://kit.fontawesome.com/a945d9a40f.js"></script>
    <script src="https://code.jquery.com/jquery-1.10.2.js"></script>
    <script src="https://code.jquery.com/ui/1.10.4/jquery-ui.js"></script>
    <script type="text/javascript" src="../internal/jQuery/jQuery.js"></script>
    <link rel="stylesheet" type="text/css" href="../internal/styleSheet/style.css">
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.0/css/bootstrap.min.css">


</head>

<?php
    // set error handling
    error_reporting(0);
    // Initalise session data
    session_start();

    $query = "SELECT * FROM user ";
    $result = filterTable($query);
    $numUser = mysqli_num_rows($result);

    $query = "SELECT * FROM borrow ";
    $result = filterTable($query);
    $numBorrow = mysqli_num_rows($result);

    if (isset($_POST['search'])) {
        $valueToSearch = $_POST['valueToSearch'];
        $query = "SELECT * FROM book WHERE CONCAT(book_id, book_title, book_type, book_author, book_year, book_avaliability) LIKE '%" . $valueToSearch . "%' ";
        $result = filterTable($query);
        $numBook = mysqli_num_rows($result);
    } else if(isset($_POST['sortBookTitle'])) {
        $query = "SELECT * FROM book ORDER BY `book_title` ASC ";
        $result = filterTable($query);
        $numBook = mysqli_num_rows($result);       
    } else if(isset($_POST['sortBookType'])) {
        $query = "SELECT * FROM book ORDER BY `book_type` ASC ";
        $result = filterTable($query);
        $numBook = mysqli_num_rows($result);        
    } else {
        $query = "SELECT * FROM book ORDER BY `book_id` ASC ";
        $result = filterTable($query);
        $numBook = mysqli_num_rows($result);
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
            <form name="searchFrm" method="post" action="<?php echo $self ?> ">
                <div class="search">
                    <i class="fa-solid fa-magnifying-glass"></i>
                    <input type="text" name="valueToSearch" placeholder="Enter text to search"> <br>
                    <input type="submit" class="btn btn-success" name="search" value="Filter">

                </div>
            </form>
            <div class="profile">
                <i class="fa-solid fa-user"> Hello Admin <?php printf($user); ?></i>
                <a title="Logout" href="../external/profile.php"><img src="../internal/images/adminpic.png"></a>
            </div>

        </div>
        <h3 class="i-name">Library Catalogue</h3>
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
            <a href="admin_borrow.php"><i class="fa-solid fa-address-book"></i></a>
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
                <i class="fa-solid fa-calendar-day"></i>
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

        <div class="board">
            <form name="form1" action="<?php echo $self ?>" method="post">
                <div>
                    <?php
                    if ($_SESSION['message']) {
                        echo $_SESSION['message'];
                    }

                    unset($_SESSION['message']);

                    ?>
                </div>
                <table id="listTable">
                    <thead>
                        <tr>
                            <th>Book ID</th>
                            <th>Book Name <button title="Click to sort" name="sortBookTitle" ><i class='fas fa-sort-alpha-down'></i></button> </th>
                            <th>Book Type<button title="Click to sort" name="sortBookType" ><i class='fas fa-sort-alpha-down'></i></button></th>
                            <th>Book Author</th>
                            <th>Publication Date</th>
                            <th>Book Avaliability</th>
                            <th>Update Record</th>
                            <th>Delete Record</th>
                        </tr>
                    </thead>
                    
                    <tbody>
                            <?php if($numBook==0) { 
                                    echo "<tr><td >Empty</td> </tr>";
                                }
                            ?>
                        <?php
                        while ($book = mysqli_fetch_array($result)) { ?>
                            <tr>
                                <td align="center"><?php echo $book["book_id"]; ?>
                                <td align="center"><?php echo $book["book_title"]; ?></td>
                                <td align="center"><?php echo $book["book_type"]; ?></td>
                                <td align="center"><?php echo $book["book_author"]; ?></td>
                                <td align="center"><?php echo $book["book_year"]; ?></td>
                                <td align="center"><?php echo $book["book_avaliability"]; ?></td>
                                <td align="center">
                                    <!-- Hide update action for admin -->
                                    <?php if ($user["user_type"] !== 'admin') { ?>
                                        <?php echo "<a href='../external/update_book.php?update_bookid={$book['book_id']}'> Update </a>"; ?>
                                </td>
                            <?php } ?>
                            </td>
                            <td align="center">
                                <!-- Hide delete action for admin -->
                                <?php if ($user["user_type"] !== 'admin') { ?>
                                    <?php echo "<a onClick=\"javascript:return confirm('Do you to delete this');\" href='../external/delete_book.php?delete_bookid={$book['book_id']}'> Delete </a>"; ?>
                            </td>
                        <?php } ?>
                            </tr>
                        <?php
                        }
                        ?>
                    </tbody>
                </table>
            </form>
        </div>
    </section>


<script>
  function sortTable() {
  var table, rows, switching, i, x, y, shouldSwitch;
  table = document.getElementById("listTable");
  switching = true;
  /*Make a loop that will continue until
  no switching has been done:*/
  while (switching) {
    //start by saying: no switching is done:
    switching = false;
    rows = table.rows;
    /*Loop through all table rows (except the
    first, which contains table headers):*/
    for (i = 1; i < (rows.length - 1); i++) {
      //start by saying there should be no switching:
      shouldSwitch = false;
      /*Get the two elements you want to compare,
      one from current row and one from the next:*/
      x = rows[i].getElementsByTagName("TD")[1];
      y = rows[i + 1].getElementsByTagName("TD")[1];
      //check if the two rows should switch place:
      if (x.innerHTML.toLowerCase() > y.innerHTML.toLowerCase()) {
        //if so, mark as a switch and break the loop:
        shouldSwitch = true;
        break;
      }
    }
    if (shouldSwitch) {
      /*If a switch has been marked, make the switch
      and mark that a switch has been done:*/
      rows[i].parentNode.insertBefore(rows[i + 1], rows[i]);
      switching = true;
    }
  }
}
</script>


</body>

</html>