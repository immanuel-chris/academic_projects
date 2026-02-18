<?php
session_start();
include $_SERVER['DOCUMENT_ROOT']."/db_conn.php";

//user information
$sqlUserId = "SELECT * FROM users WHERE id='".$_SESSION['id']."' LIMIT 1";
$resultId = mysqli_query($conn, $sqlUserId);
$rowFromIdResult = mysqli_fetch_assoc($resultId);

//all unread chat amount
$sqlChats = "SELECT * FROM messages WHERE receiver='".$rowFromIdResult['username']."' AND isread=0 AND isorgchat=0";
$resultChats = mysqli_query($conn, $sqlChats);
$notifChats = mysqli_num_rows($resultChats);

//all unread org chats amount
$sqlOrgChats = "SELECT * FROM orgchatreadby WHERE isread=0 AND username='".$rowFromIdResult['username']."'";
$resultOrgChats = mysqli_query($conn, $sqlOrgChats);
$notifOrgChats = mysqli_num_rows($resultOrgChats);

$totalNotifs = $notifChats + $notifOrgChats;

echo json_encode(["contents" => $totalNotifs]);
exit();