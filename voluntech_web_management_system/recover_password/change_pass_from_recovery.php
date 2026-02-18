<?php
session_start();
ob_start();

include $_SERVER['DOCUMENT_ROOT']."/db_conn.php";

if (isset($_POST['password']) && isset($_POST['re_password'])) {
    function validate($data) {
        $data = trim($data);
        $data = stripslashes($data);
        $data = htmlspecialchars($data);
        return $data;
    }
    $password = validate($_POST['password']);
    $repassword = validate($_POST['re_password']);

    if (empty($password)) {
        $token = $_GET['token'];
        header("Location: change_from_recovery.php?error=Password must not be empty&?token='$token'");
        exit();
    }
    else if ($password !== $repassword) {
        $token = $_GET['token'];
        header("Location: change_from_recovery.php?error=Passwords must match&?token='$token'");
        exit();
    }
    else {
        $password = md5($password);
        $token = $_GET['token'];
        $sqlResult = mysqli_query($conn, "UPDATE users SET password='$password' WHERE verificationToken='$token'");
        if ($sqlResult) {
            $changeResult = mysqli_query($conn, "SELECT * FROM users WHERE verificationToken='$token' LIMIT 1");
            $user = mysqli_fetch_assoc($changeResult);
            $username = $user['username'];

            $_SESSION['id'] = $user['id'];
            $_SESSION['verified'] = $user['verified'];

            header("Location: change_pass_success.php?token=".$token);
            exit();
        }
        else {
            $token = $_GET['token'];
            header("Location: change_from_recovery.php?error=Something weird happened&?token='$token'");
            exit();
        }
    }
}
?>