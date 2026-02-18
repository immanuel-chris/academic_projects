<?php
session_start();
include $_SERVER['DOCUMENT_ROOT']."/db_conn.php";

$sqlUserId = "SELECT * FROM users WHERE id='".$_SESSION['id']."' LIMIT 1";
$resultId = mysqli_query($conn, $sqlUserId);
$rowFromIdResult = mysqli_fetch_assoc($resultId);

//get latest message
$sqlOrg = "SELECT * FROM messages WHERE isorgchat='1' ORDER BY id DESC LIMIT 1";
$resultOrgMsg = mysqli_query($conn, $sqlOrg);

if (mysqli_num_rows($resultOrgMsg) > 0) {
    $latestOrgMessage = mysqli_fetch_assoc($resultOrgMsg);
    
    //get name of the sender of latest message
    $sqlName = "SELECT * FROM users WHERE username='".$latestOrgMessage['username']."' LIMIT 1";
    $resultUsn = mysqli_query($conn, $sqlName);
    $rowFromUsn = mysqli_fetch_assoc($resultUsn);
    $middleName = !empty($rowFromUsn['middlename']) ? " ".$rowFromUsn['middlename']." " : " " ;
    // $latestOrgMessage['username'] === $rowFromIdResult['username'] ? "You" : getNameFromUsername($latestOrgMessage['username'], $conn);

    $fullname = $latestOrgMessage['username'] === $rowFromIdResult['username'] ? "You" : $rowFromUsn['firstname'].$middleName.$rowFromUsn['familyname'];

    //send final message
    echo json_encode(["contents" => $fullname.": ".mb_strimwidth($latestOrgMessage['contents'], 0, 50, "...")]);
}
else {
    echo json_encode(["contents" => "No messages yet..."]);
}
exit();