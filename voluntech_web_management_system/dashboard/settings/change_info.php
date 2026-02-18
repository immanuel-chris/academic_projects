<?php
session_start();
include $_SERVER['DOCUMENT_ROOT']."/db_conn.php";

$profileId = $_SESSION['id'];

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

if (!empty($email)) {
    mysqli_query($conn, "UPDATE users SET email='$email' WHERE id=".$profileId);
}
if (!empty($firstname)) {
    mysqli_query($conn, "UPDATE users SET firstname='$firstname' WHERE id=".$profileId);
}
if (!empty($middlename)) {
    mysqli_query($conn, "UPDATE users SET middlename='$middlename' WHERE id=".$profileId);
}
if (!empty($familyname)) {
    mysqli_query($conn, "UPDATE users SET familyname='$familyname' WHERE id=".$profileId);
}
header("Location: http://".$_SERVER['HTTP_HOST']."/dashboard?page=settings&success=Info changed successfully");
exit();
?>