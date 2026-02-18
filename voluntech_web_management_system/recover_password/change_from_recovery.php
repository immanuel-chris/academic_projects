<!DOCTYPE html>
<html>
<head>
    <title>Change Password</title>
    <?php echo '<link rel="stylesheet" href="http://'. $_SERVER['HTTP_HOST'] .'/style.css">' ?>
</head>
<?php
session_start();
ob_start();
include $_SERVER['DOCUMENT_ROOT']."/db_conn.php";

$token = $_GET['token'];

$sql = "SELECT * FROM users WHERE verificationToken='$token' LIMIT 1";
$result = mysqli_query($conn, $sql);

if (mysqli_num_rows($result) > 0) {
?>
<body class="login">
    <form class="signup" <?php echo "action=\"change_pass_from_recovery.php?token=".$token."\"" ?> method="post">
        <h2 class="login">Change Password</h2>
        <?php if (isset($_GET['error'])) { ?>
            <p class="error"><?php echo $_GET['error']; ?></p>
        <?php } ?>
        <label>New Password</label>
        <input type="password" name="password" placeholder="Password">
        
        <label>Re-enter New Password</label>
        <input type="password" name="re_password" placeholder="Re-enter Password">

        <button type="submit">Change Password</button>
    </form>
</body>
<?php
}
else {
?>
<body class="login">
    <main class="small">
        <p class="center-block">...you aren't supposed to be here</p>
    </main>
</body>
<?php
}
?>
</html>