<?php
session_start();
ob_start();

include $_SERVER['DOCUMENT_ROOT']."/db_conn.php";

use PHPMailer\PHPMailer\PHPMailer;
use PHPMailer\PHPMailer\Exception;

require '../phpmailer/src/Exception.php';
require '../phpmailer/src/PHPMailer.php';
require '../phpmailer/src/SMTP.php';

if (isset($_POST['email'])) {
    function validate($data) {
        $data = trim($data);
        $data = stripslashes($data);
        $data = htmlspecialchars($data);
        return $data;
    }
    $email = validate($_POST['email']);

    if (empty($email)) {
        header("Location: index.php?error=E-mail cannot be left blank");
        exit();
    }
    else if (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
        header("Location: index.php?error=Not a valid e-mail");
        exit();
    }
    else {
        $sqlUser = "SELECT * FROM users WHERE email='$email'";
        $resultUser = mysqli_query($conn, $sqlUser);
        $rowFromUserResult = mysqli_fetch_assoc($resultUser);

        if (mysqli_num_rows($resultUser) === 1) {
            $verificationToken = bin2hex(random_bytes(16));
            
            $sqlAddToken = "UPDATE users SET verificationToken='$verificationToken' WHERE email='$email'";

            $addTokenResult = mysqli_query($conn, $sqlAddToken);
            if ($addTokenResult) {
                $verifyLink = "http://".$_SERVER['HTTP_HOST']."/recover_password/change_from_recovery.php?token=".$verificationToken;

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

                $mail->Subject = "Voluntech Password Recovery";
                $mail->Body = "If you don't ever remember trying to recover your account, please disregard. Otherwise, click on this link to change your password: ".$verifyLink;
                $mail->send();
                header("Location: index.php?success=A verification link has been sent to your e-mail, please check.");
                exit();
            }
            else {
                header("Location: index.php?error=Something weird happened. Please try again");
                exit();
            }
        }
        else {
            header("Location: index.php?error=Invalid e-mail");
            exit();
        }
    }
}
?>