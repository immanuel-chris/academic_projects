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

//get user stuff
$sqlUserId = "SELECT * FROM users WHERE id='".$_SESSION['id']."' LIMIT 1";
$resultId = mysqli_query($conn, $sqlUserId);
$rowFromIdResult = mysqli_fetch_assoc($resultId);

//set values
$contents = validate($_GET['message']);
$targetId = validate(($_GET['id']));
$targetName = getUsernameFromId($targetId, $conn);
$senderName = $rowFromIdResult['username'];
$isOrgChat = $targetId == -1 ? 1 : 0;

//add to messages table
$dateSent = date("Y-m-d H:i:s");
$sqlAddToMessages = "INSERT INTO messages(contents, username, receiver, datesent, isorgchat) VALUES ('$contents', '$senderName', '$targetName', '$dateSent', '$isOrgChat')";
mysqli_query($conn, $sqlAddToMessages);

//if is to the org chat, send to orchatreadby
if ($isOrgChat) {
    $lastId = mysqli_insert_id($conn);
    //get all usernames
    $sqlAllUsernames = "SELECT * FROM users";
    $resultUsernames = mysqli_query($conn, $sqlAllUsernames);
    foreach ($resultUsernames as $rUsernamesRow) {
        $sqlAddToOrgReadBy = "INSERT INTO orgchatreadby(messageid, username) VALUES ('$lastId', '".$rUsernamesRow['username']."')";
        mysqli_query($conn, $sqlAddToOrgReadBy);
    }
}

echo json_encode(["status" => "peepeepoopoo"]);
exit();