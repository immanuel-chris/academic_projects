<?php
session_start();
include $_SERVER['DOCUMENT_ROOT']."/db_conn.php";

function validate($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}

//get messageid
$messageId = validate($_GET['messageid']);

//remove row containin message
mysqli_query($conn, "DELETE FROM messages WHERE id='".$messageId."'");