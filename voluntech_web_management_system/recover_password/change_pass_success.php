<?php
session_start();
ob_start();
include $_SERVER['DOCUMENT_ROOT']."/db_conn.php";

$token = $_GET['token'];
$sql = "SELECT * FROM users WHERE verificationToken='$token' LIMIT 1";
$result = mysqli_query($conn, $sql);
$user = mysqli_fetch_assoc($result);
$canRedirect = false;

if (mysqli_num_rows($result) > 0) {
    $canRedirect = true;
    $verifyMessage = "Your password has successfully been changed. You will be redirected shortly...";
    mysqli_query($conn, "UPDATE users SET verificationToken=NULL WHERE id=".$user['id']);
}
else {
    $verifyMessage = "An error occurred";
}
?>

<!DOCTYPE html>
<html>
<head>
    <title>Change Password</title>
    <?php echo '<link rel="stylesheet" href="http://'. $_SERVER['HTTP_HOST'] .'/style.css">' ?>
</head>
<body class="login">
    <main class="small">
        <p class="center-block"><?php echo $verifyMessage ?></p>
    </main>
</body>
<?php 
    if ($canRedirect) {
        echo '
            <script>
                setTimeout(function(){
                    window.location.href = "http://'. $_SERVER['HTTP_HOST'] .'/dashboard";
                }, 5000);
            </script>
        ';
    }
?>
</html>