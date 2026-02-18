<?php
session_start();
ob_start();

include $_SERVER['DOCUMENT_ROOT']."/db_conn.php";

use PHPMailer\PHPMailer\PHPMailer;
use PHPMailer\PHPMailer\Exception;

require '../phpmailer/src/Exception.php';
require '../phpmailer/src/PHPMailer.php';
require '../phpmailer/src/SMTP.php';

$profileId = $_SESSION['id'];
$sqlUserId = "SELECT * FROM users WHERE id='".$_SESSION['id']."'";
$resultId = mysqli_query($conn, $sqlUserId);
$rowFromIdResult = mysqli_fetch_assoc($resultId);

if (!$rowFromIdResult['verified']) {
    $verificationToken = $rowFromIdResult['verificationToken'];
    $verifyLink = "http://".$_SERVER['HTTP_HOST']."/register/verify.php?token=".$verificationToken;

    $mail = new PHPMailer(true);
    $mail->isSMTP();
    $mail->Host = 'smtp.gmail.com';
    $mail->SMTPAuth = true;
    $mail->Username = 'voluntech126@gmail.com';
    $mail->Password = 'kavsonwjoioklrbn';
    $mail->SMTPSecure = 'ssl';
    $mail->Port = 465;

    $mail->setFrom('voluntech126@gmail.com');
    $mail->addAddress($_SESSION['email']);

    $mail->Subject = "Voluntech Verification";
    $mail->Body = "If this e-mail has reached you, it means you're at the final step of signing up to Voluntech! Click on this link to finish: ".$verifyLink;
    $mail->send();
?>
<!DOCTYPE html>
<html>
<head>
    <title>Register to Voluntech</title>
    <?php echo '<link rel="stylesheet" href="http://'. $_SERVER['HTTP_HOST'] .'/style.css">' ?>
</head>
<body class="login">
    <main class="small">
        <p class="center-block">An e-mail from voluntech126@gmail.com should be sent to your email inbox. Please check it out to be able to finish registration. Refresh the page if you haven't received the e-mail, or <?php echo '<a href="http://'.$_SERVER['HTTP_HOST'].'/login/logout.php">click here</a>'; ?> to cancel and go back to the login page.</p>
    </main>
</body>
</html>
<?php 
}
else {
?>
<!DOCTYPE html>
<html>
<head>
    <title>Register to Voluntech</title>
    <?php echo '<link rel="stylesheet" href="http://'. $_SERVER['HTTP_HOST'] .'/style.css">' ?>
</head>
<body class="login">
    <main class="small">
        <p class="center-block">...how did you get here????</p>
        <?php echo '<button onclick="location.href=\'http://'. $_SERVER['HTTP_HOST'] .'/login\';">Login</button>' ?>
    </main>
</body>
</html>
<?php
}
?>