<?php
session_start();

include $_SERVER['DOCUMENT_ROOT']."/db_conn.php";

use PHPMailer\PHPMailer\PHPMailer;
use PHPMailer\PHPMailer\Exception;

require '../phpmailer/src/Exception.php';
require '../phpmailer/src/PHPMailer.php';
require '../phpmailer/src/SMTP.php';

function validate($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}

$email = validate($_POST['email']);
$firstname = validate($_POST['firstname']);
$middlename = validate($_POST['middlename']);
$familyname = validate($_POST['familyname']);
$username = validate($_POST['username']);
$birthday = validate($_POST['birthday']);
$password = validate($_POST['password']);
$re_password = validate($_POST['re_password']);

$user_data = 'suname='.$dbname.'&firstname='.$firstname.'&middlename='.$middlename.'&familyname='.$familyname;

if (empty($email)) {
    header("Location: index.php?error=E-mail is required&$user_data");
    exit();
}
else if (empty($firstname)) {
    header("Location: index.php?error=First name is required&$user_data");
    exit();
}
else if (empty($familyname)) {
    header("Location: index.php?error=Family name is required&$user_data");
    exit();
}
else if (empty($username)) {
    header("Location: index.php?error=Username is required&$user_data");
    exit();
}
else if (empty($birthday)) {
    header("Location: index.php?error=Birthday is required&$user_data");
    exit();
}
else if (empty($password)) {
    header("Location: index.php?error=Password is required&$user_data");
    exit();
}
else if (empty($re_password)) {
    header("Location: index.php?error=Password must be re-entered for validation purposes&$user_data");
    exit();
}
else if ($password !== $re_password) {
    header("Location: index.php?error=Passwords must match&$user_data");
    exit();
}
else if (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
    header("Location: index.php?error=Not a valid e-mail&$user_data");
    exit();
}
else {
    $password = md5($password);
    $sqlName = "SELECT * FROM users WHERE username='$username'";
    $sqlEmail = "SELECT * FROM users WHERE email='$email'";
    $resultName = mysqli_query($conn, $sqlName);
    $resultEmail = mysqli_query($conn, $sqlEmail);

    if (mysqli_num_rows($resultName) > 0) {
        header("Location: index.php?error=That username has been taken, try another one&$user_data");
        exit();
    }
    else if (mysqli_num_rows($resultEmail) > 0) {
        header("Location: index.php?error=That e-mail has been taken, try another one&$user_data");
        exit();
    }
    else {
        $verificationToken = bin2hex(random_bytes(16));
        $sql2Users = "INSERT INTO users(email, username, password, firstname, middlename, familyname, birthday, verificationToken) VALUES('$email', '$username', '$password', '$firstname', '$middlename', '$familyname', '$birthday', '$verificationToken')";
        $result2 = mysqli_query($conn, $sql2Users);
        if ($result2) {
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
            $mail->addAddress($email);
        
            $mail->Subject = "Voluntech Verification";
            $mail->Body = "If this e-mail has reached you, it means you're at the final step of signing up to Voluntech! Click on this link to finish: ".$verifyLink;
            $mail->send();

            header("Location: http://".$_SERVER['HTTP_HOST']."/login?success=You're almost successfully registered! Check your e-mail!");
            exit();
        }
        else {
            header("Location: index.php?error=Something weird happened...&$user_data");
            exit();
        }
    }
}