<?php
session_start();
include $_SERVER['DOCUMENT_ROOT']."/db_conn.php";

function validate($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}

$taskId = validate($_POST['taskid']);

//remove row containin task
mysqli_query($conn, "DELETE FROM tasks WHERE id='".$taskId."'");

//remove all rows containin task
mysqli_query($conn, "DELETE FROM taskassocs WHERE taskid='".$taskId."'");

header("Location: http://".$_SERVER['HTTP_HOST']."/dashboard?page=tasks&success=Task deleted successfully");
exit();