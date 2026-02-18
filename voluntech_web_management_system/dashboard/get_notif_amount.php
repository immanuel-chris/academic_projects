<?php
session_start();
include $_SERVER['DOCUMENT_ROOT']."/db_conn.php";

//user information
$sqlUserId = "SELECT * FROM users WHERE id='".$_SESSION['id']."' LIMIT 1";
$resultId = mysqli_query($conn, $sqlUserId);
$rowFromIdResult = mysqli_fetch_assoc($resultId);

//notif count
$sqlNotifs = "SELECT * FROM notification WHERE username='".$rowFromIdResult['username']."' AND isread=0";
$resultNotifs = mysqli_query($conn, $sqlNotifs);
$notifCount = mysqli_num_rows($resultNotifs);

echo json_encode(["contents" => $notifCount]);
exit();