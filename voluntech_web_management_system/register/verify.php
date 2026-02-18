<?php
session_start();
ob_start();
include $_SERVER['DOCUMENT_ROOT']."/db_conn.php";

$token = $_GET['token'];

$sql = "SELECT * FROM users WHERE verificationToken='$token' LIMIT 1";
$result = mysqli_query($conn, $sql);

$canRedirect = false;

if (mysqli_num_rows($result) > 0) {
    $user = mysqli_fetch_assoc($result);
    $username = $user['username'];
    $update = "UPDATE users SET verified=1 WHERE id=".$user['id'];
    if (mysqli_query($conn, $update)) {
        $verifyMessage = "Your account has successfully been verified. You will be redirected shortly...";

        mysqli_query($conn, "UPDATE users SET verificationToken=NULL WHERE id=".$user['id']);
        $_SESSION['id'] = $user['id'];
        $_SESSION['verified'] = 1;
        $canRedirect = true;
    }
    else {
        $verifyMessage = "An error occurred.";
    }
} 
else {
    $verifyMessage = "Invalid verification link.";
}
?>

<!DOCTYPE html>
<html>
<head>
    <title>Register to Voluntech</title>
    <?php echo '<link rel="stylesheet" href="http://'. $_SERVER['HTTP_HOST'] .'/style.css">' ?>
</head>
<body class="login">
    <main class="small">
        <?php echo $verifyMessage ?>
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