<?php
session_start();
include $_SERVER['DOCUMENT_ROOT']."/db_conn.php";

function validate($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}

function getUsernameFromId($id, $conn) {
    $sqlIdInp = "SELECT * FROM users WHERE id='$id' LIMIT 1";
    $resultIdInp = mysqli_query($conn, $sqlIdInp);
    $rowFromIdInp = mysqli_fetch_assoc($resultIdInp);
    if (!empty($rowFromIdInp)) return $rowFromIdInp['username'];
    else return "";
}

//set data
$sqlUserId = "SELECT * FROM users WHERE id='".$_SESSION['id']."' LIMIT 1";
$resultId = mysqli_query($conn, $sqlUserId);
$rowFromIdResult = mysqli_fetch_assoc($resultId);

if (isset($_GET['chat']) && $_GET['chat'] != -1) {
    $sqlChatsUnread = "SELECT * FROM messages WHERE isorgchat=0 AND username='".getUsernameFromId($_GET['chat'], $conn)."' AND receiver='".$rowFromIdResult['username']."' AND isread=0";
    $resultChats = mysqli_query($conn, $sqlChatsUnread);
    foreach ($resultChats as $rChatsRow) {
        mysqli_query($conn, "UPDATE messages SET isread=1 WHERE id='".$rChatsRow['id']."'");
    }
}
else {
    $sqlChatsUnread = "SELECT * FROM orgchatreadby WHERE username='".$rowFromIdResult['username']."' AND isread=0";
    $resultChats = mysqli_query($conn, $sqlChatsUnread);
    foreach ($resultChats as $rChatsRow) {
        mysqli_query($conn, "UPDATE orgchatreadby SET isread=1 WHERE id='".$rChatsRow['id']."'");
    }
}