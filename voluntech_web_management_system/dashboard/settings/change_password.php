<?php
session_start();
include $_SERVER['DOCUMENT_ROOT']."/db_conn.php";

$profileId = $_SESSION['id'];
$sqlUserId = "SELECT * FROM users WHERE id=".$profileId;
$resultId = mysqli_query($conn, $sqlUserId);
$rowFromIdResult = mysqli_fetch_assoc($resultId);

function validate($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}

$currentpassword = validate($_POST['currentpassword']);
$newpassword = validate($_POST['newpassword']);
$renewpassword = validate($_POST['renewpassword']);

if (empty($currentpassword)) {
    header("Location: http://".$_SERVER['HTTP_HOST']."/dashboard?page=settings&error=You need to enter your old password");
    exit();
}
else if (empty($newpassword)) {
    header("Location: http://".$_SERVER['HTTP_HOST']."/dashboard?page=settings&error=Please enter your new password");
    exit();
}
else if (empty($renewpassword)) {
    header("Location: http://".$_SERVER['HTTP_HOST']."/dashboard?page=settings&error=Please re-enter your new password");
    exit();
}
else if ($newpassword != $renewpassword) {
    header("Location: http://".$_SERVER['HTTP_HOST']."/dashboard?page=settings&error=The new password and the re-entered one must be the same");
    exit();
}
else {
    $currentpassword = md5($currentpassword);
    $newpassword = md5($newpassword);
    if ($currentpassword == $rowFromIdResult['password']) {
        mysqli_query($conn, "UPDATE users SET password='$newpassword' WHERE id=".$profileId);
        header("Location: http://".$_SERVER['HTTP_HOST']."/dashboard?page=settings&success=Password changed successfully");
        exit();
    }
    else {
        header("Location: http://".$_SERVER['HTTP_HOST']."/dashboard?page=settings&error=You need to enter your old password correctly");
        exit();
    }
}
?>