<?php
session_start();
include $_SERVER['DOCUMENT_ROOT']."/db_conn.php";

function validate($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}
$username = validate($_POST['username']);
$taskid = validate($_POST['taskid']);

//mark as done on taskassocs
$updateSql = mysqli_query($conn, "UPDATE taskassocs SET finished='0' WHERE username='$username' AND taskid='$taskid'");
header("Location: http://".$_SERVER['HTTP_HOST']."/dashboard?page=tasks&success=Task marked successfully");
exit();
?>