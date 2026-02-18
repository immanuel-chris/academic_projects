<?php
function validate($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}
?>

<!-- button for user list -->
<?php echo "<button onclick=\"location.href='http://".$_SERVER['HTTP_HOST']."/dashboard?page=users'\" style=\"float: left; margin-right: 1100px;\">Return to user directory</button>" ?>
<div class="blank-space"></div>
<div class="chat-container">
    <div class="chat-sidebar" id="chat-sidebar">
        <?php
            //a group chat for all members of the organization is first
            //group chat for org is first
            $sqlOrgMessages = "SELECT * FROM messages WHERE isorgchat='1' ORDER BY id DESC LIMIT 1";
            $resultOrgMsg = mysqli_query($conn, $sqlOrgMessages);
            $latestOrgMessage = mysqli_fetch_assoc($resultOrgMsg);
        ?>
        <?php 
        ?>
        <div class=<?php echo isset($_GET['chat']) ? ($_GET['chat'] == -1 ? "chat-sidebar-msgr-current" : "chat-sidebar-msgr") : "chat-sidebar-msgr-current" ?> id="chat-org">
            <b><?php echo ucfirst($rowFromIdResult['organization']); ?> (Organization Chat)</b>
            <br />
            <?php
            if ($latestOrgMessage) {
                $lastSenderName = $latestOrgMessage['username'] === $rowFromIdResult['username'] ? "You" : getNameFromUsername($latestOrgMessage['username'], $conn);
                $latestMessageContent = $lastSenderName.": ".mb_strimwidth($latestOrgMessage['contents'], 0, 50, "...");
                echo "<span class=\"chat-sidebar-latest-msg\" id=\"org-chat\">".$latestMessageContent."</span>";
            }
            else {
                echo "<span class=\"chat-sidebar-latest-msg\" id=\"org-chat\">No messages yet...</span>";
            }
            ?>
        </div>

        <!-- this section is for when the user has just started to chat with a random person -->
        <!-- once they send a message it gets moved out from here to the other-ppl-chat -->
        <div id="recent-choice-chat">
            <?php 
                if (isset($_GET['chat'])) {
                    if ($_GET['chat'] != -1) {
                        $choiceUsername = getUsernameFromId($_GET['chat'], $conn);
                        $loggedInUsername = $rowFromIdResult['username'];
                        //get all chat logs to test for if it has a match with anyone the person has had convos with
                        $sqlCheckHistory = "SELECT 1 
                        FROM messages 
                        WHERE (username = ? AND receiver = ?) 
                        OR (username = ? AND receiver = ?)
                        LIMIT 1";
                        $stmt = mysqli_prepare($conn, $sqlCheckHistory);
                        mysqli_stmt_bind_param($stmt, 'ssss', $loggedInUsername, $choiceUsername, $choiceUsername, $loggedInUsername);
                        mysqli_stmt_execute($stmt);
                        $resultHistory = mysqli_stmt_get_result($stmt);
                        $existingHistory = mysqli_fetch_assoc($resultHistory);
                        $profilePic = getImgFromUsername($choiceUsername, $conn);

                        if (!$existingHistory) {
                            echo "<div class=\"chat-sidebar-msgr-current\" id=\"chat-".$_GET['chat']."\">";
                            echo "<img src=\"http://".$_SERVER['HTTP_HOST']."/media/".$profilePic."\" width=60>";
                            echo "<b>".getNameFromUsername($choiceUsername, $conn)."</b>";
                            echo "<br />";
                            echo "<span class=\"chat-sidebar-latest-msg\">No messages yet...</span>";
                            echo "</div>";
                        }
                    }
                }
            ?>
        </div>

        <!-- by this point using some kind of dynamic js more clickable areas -->
        <!-- using <div class=\"chat-sidebar-msgr\"></div> -->
        <?php
            $sqlChats = "SELECT m1.*
            FROM messages m1
            INNER JOIN (
                SELECT 
                    IF(username = '".$rowFromIdResult['username']."', receiver, username) AS chat_partner,
                    MAX(datesent) AS max_date
                FROM messages
                WHERE isorgchat = '0' 
                AND (username = '".$rowFromIdResult['username']."' OR receiver = '".$rowFromIdResult['username']."')
                GROUP BY chat_partner
            ) m2 ON (
                (m1.username = '".$rowFromIdResult['username']."' AND m1.receiver = m2.chat_partner) OR 
                (m1.receiver = '".$rowFromIdResult['username']."' AND m1.username = m2.chat_partner)
            ) AND m1.datesent = m2.max_date
            WHERE m1.isorgchat = '0'
            ORDER BY m1.datesent DESC;";

            $resultChats = mysqli_query($conn, $sqlChats);
            $chats = mysqli_fetch_all($resultChats, MYSQLI_ASSOC);

            // HTML for sidebar chats
                echo "<div id=\"other-ppl-chat\">"; //this is to surround the chats for all other ppl to so that this refreshes easily in js
            foreach ($chats as $chat) {
                //name of the person the user is talking with
                $chatParticipant = $chat['username'] === $rowFromIdResult['username'] ? $chat['receiver'] : $chat['username'];
                //name of last sender
                $chatSender = $chat['username'] === $rowFromIdResult['username'] ? "You: " : "";
                //chatId is the id of the person the user is talking with
                $sqlGetUserId = "SELECT * FROM users WHERE username='".$chatParticipant."' LIMIT 1";
                $chatId = mysqli_fetch_assoc(mysqli_query($conn, $sqlGetUserId))['id'];
                $chatClass = isset($_GET['chat']) ? ($_GET['chat'] === $chatId ? "chat-sidebar-msgr-current" : "chat-sidebar-msgr") : "chat-sidebar-msgr";
                $latestMessage = $chatSender.mb_strimwidth($chat['contents'], 0, 50, "...");
                $profilePic = mysqli_fetch_assoc(mysqli_query($conn, $sqlGetUserId))['image'];

                echo "<div class={$chatClass} id=\"chat-{$chatId}\">";
                echo "<img src=\"http://".$_SERVER['HTTP_HOST']."/media/".$profilePic."\" width=60>";
                echo "<b>".getNameFromUsername($chatParticipant, $conn)."</b>
                <br />
                <span class=\"chat-sidebar-latest-msg\">{$latestMessage}</span>
                </div>";
            }
        ?>
        </div>
    </div>

    <!-- now the actual chat ui -->
    <!-- by default  -->
    <div class="chat-main-contents">
        <div id="chat-messages" class="chat-messages">
            <?php
                if (isset($_GET['chat']) && $_GET['chat'] != -1) {
                    //for individual chats
                    $sqlIndivChat = "SELECT * FROM messages WHERE isorgchat=0 AND (username='".$rowFromIdResult['username']."' AND receiver='".getUsernameFromId($_GET['chat'], $conn)."') OR (username='".getUsernameFromId($_GET['chat'], $conn)."' AND receiver='".$rowFromIdResult['username']."') ORDER BY datesent DESC LIMIT 8";
                    $resultMessageHist = mysqli_query($conn, $sqlIndivChat);
                }
                else {
                    $sqlGroupChat = "SELECT * FROM messages WHERE isorgchat=1 ORDER BY datesent DESC LIMIT 8";
                    $resultMessageHist = mysqli_query($conn, $sqlGroupChat);
                }

                //get chats
                $chats = array_reverse(mysqli_fetch_all($resultMessageHist, MYSQLI_ASSOC));

                //get date to be put on the top
                $lastDate = null;

                //start the msg string
                $msg = "";
                
                //print messages
                foreach ($chats as $chatMsg) {
                    $currentDate = date('Y-m-d', strtotime($chatMsg['datesent'])); // Extract the date part

                    // Check if the date has changed since the last message
                    if ($lastDate !== $currentDate) {
                        $displayDate = $currentDate === date('Y-m-d') ? "Today" : date('F jS, Y', strtotime($currentDate));
                        $msg = $msg."<div class=\"chat-date-banner\">{$displayDate}</div></br>";
                        $lastDate = $currentDate; // Update lastDate to the current message's date
                        if (!isset($firstDate)) $firstDate = $currentDate;
                    }

                    $msgClass = ($chatMsg['username'] == $rowFromIdResult['username']) ? "chat-message-contents-logged-in" : "chat-message-contents-other";
                    $msgSender = getNameFromUsername($chatMsg['username'], $conn);
                    $profilePic = getImgFromUsername($chatMsg['username'], $conn);

                    //set the time and date message was sent
                    $dateTime = new DateTime($chatMsg['datesent']);
                    $formattedDate = $dateTime->format('F jS, Y');
                    $formattedTime = $dateTime->format('H:i:s');
                    $sentTime = $formattedTime.", ".$formattedDate;

                    $msg = $msg."<div id=\"blank-space-".$chatMsg['id']."\" class=\"chat-blank-space\"></div>
                    <div class=\"{$msgClass}\" id='message-".$chatMsg['id']."'>
                    <img src=\"http://".$_SERVER['HTTP_HOST']."/media/".$profilePic."\" width=60>
                    <div class=\"chat-message-content\">
                    <div class=\"chat-message-username\"><b>".$msgSender."</div></b> <br />
                    <div class=\"chat-message-text\">".$chatMsg['contents']."</div>
                    <span class=\"chat-message-time\">".$sentTime."</span>
                    ". (($chatMsg['username'] == $rowFromIdResult['username']) ? "<span class=\"chat-message-delete-btn\" onclick=\"callDeleteMessage(".$chatMsg['id'].")\">(Delete)</span>" : "")."
                    </div></div>";
                }
                echo $msg;

                //make all messages in the chat being chosen set as read
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
            ?>
        </div>
        <form id="chatSendForm" class="chat-send-interf">
            <input type="hidden" id="sender" value="<?php echo $rowFromIdResult['username']; ?>"></input>
            <input type="hidden" id="datesent" value="<?php echo (new DateTime())->format('Y-m-d H:i:s'); ?>"></input>
            <input id="message-contents" type="text" placeholder="Type message here..."></input>
            <button id="send-button">Send</button>
        </form>
    </div>
</div>
<script>
let orgId = <?php echo isset($_GET['chat']) ? $_GET['chat'] : -1 ?>;
let offset = 0; //offset of messages to load

function loadMessageHist() {
    //load message history
    fetch('chat/get_last_message_hist.php?id='+orgId)
    .then(response => response.json())
    .then(message => {
            const chatHist = document.getElementById('chat-messages');
            chatHist.innerHTML = message.contents;
            //auto scroll messages container to bottom
            document.getElementById('chat-messages').scrollTop = document.getElementById('chat-messages').scrollHeight;
        }
    )
    .catch(error => console.error('Error:', error));
    
    //set messages on the recently opened message as read
    fetch('chat/set_messages_as_read.php?id='+orgId);
}

//for chat-org
document.getElementById('chat-org').addEventListener('click', function(event) {
    function changeOrgId() {
        orgId = -1;
        //reset old selected element & message load offset & textbar
        let oldSelected = document.getElementsByClassName('chat-sidebar-msgr-current');
        if (oldSelected.length > 0) {
            oldSelected[0].classList.add('chat-sidebar-msgr');
            oldSelected[0].classList.remove('chat-sidebar-msgr-current');
        }
        offset = 0;
        document.getElementById("chatSendForm").reset();
        //turn clicked element to new selected
        let newSelected = document.getElementById("chat-org");
        newSelected.classList.add('chat-sidebar-msgr-current');
        newSelected.classList.remove('chat-sidebar-msgr');
        //edit url bar
        let currentUrl = new URL(window.location.href);
        let baseUrl = currentUrl.origin + currentUrl.pathname;
        let newUrl = `${baseUrl}?page=chat`;
        history.pushState(null, '', newUrl);
        //remove recent-choice-chat
        if (document.getElementById('recent-choice-chat')) {
            document.getElementById('recent-choice-chat').remove();
        }
        //get messages of selected
        loadMessageHist();
    }

    if (event.target.classList.contains('chat-sidebar-msgr')) {
        changeOrgId();
    }
    else {
        let parent = event.target.closest('.chat-sidebar-msgr');
        if (parent) {
            event.stopPropagation();
            changeOrgId();
        }
    }
})

//for other-ppl-chat
document.getElementById('other-ppl-chat').addEventListener('click', function(event) {
    function changeOrgId(idTag) {
        //set orgId
        orgId = parseInt(idTag.split("-")[1], 10);
        //reset old selected element & message load offset & textbar
        let oldSelected = document.getElementsByClassName('chat-sidebar-msgr-current');
        if (oldSelected.length > 0) {
            oldSelected[0].classList.add('chat-sidebar-msgr');
            oldSelected[0].classList.remove('chat-sidebar-msgr-current');
        }
        offset = 0;
        document.getElementById("chatSendForm").reset();
        //turn clicked element to new selected
        let newSelected = document.getElementById(idTag);
        newSelected.classList.add('chat-sidebar-msgr-current');
        newSelected.classList.remove('chat-sidebar-msgr');
        //edit url bar
        let currentUrl = new URL(window.location.href);
        currentUrl.searchParams.set('chat', orgId);
        history.pushState(null, '', currentUrl.href);
        //remove recent-choice-chat
        if (document.getElementById('recent-choice-chat')) {
            document.getElementById('recent-choice-chat').remove();
        }
        //get messages of selected
        loadMessageHist();
    }

    // Check if the clicked element is exactly 'chat-sidebar-msgr', not its children
    if (event.target.classList.contains('chat-sidebar-msgr')) {
        changeOrgId(event.target.id);
    }
    else {
        // Check if the click came from within a 'chat-sidebar-msgr'
        let parent = event.target.closest('.chat-sidebar-msgr');
        if (parent) {
            // Click came from within a 'chat-sidebar-msgr' but wasn't the chat-sidebar-msgr element itself
            event.stopPropagation(); // Prevent any further action
            changeOrgId(parent.id);
        }
    }
});

//code for updating starts here
function updateOtherChatLatestMessage() {
    fetch('chat/get_other_chats_latest_message.php') //return list of latest messages for other chats
    .then(response => response.json())
    .then(message => {
        const orgOtherChatsElement = document.getElementById('other-ppl-chat');
        orgOtherChatsElement.innerHTML = message.contents;
        otherMsgs = document.getElementsByClassName('chat-sidebar-msgr');
        //set chat-sidebar-msgr-current depending on orgId
        for (let x = 0; x < otherMsgs.length; x++) {
            let elemId = parseInt(otherMsgs[x].id.split("-")[1], 10);
            if (elemId == orgId) {
                otherMsgs[x].classList.add('chat-sidebar-msgr-current');
                otherMsgs[x].classList.remove('chat-sidebar-msgr');
                break;
            }
        }
    })
    .catch(error => console.error('Error:', error));
}

function updateOrgChatLatestMessage() {
    fetch('chat/get_org_chat_latest_message.php') // This PHP script should return the latest message for the org chat
    .then(response => response.json())
    .then(message => {
        const orgChatElement = document.getElementById('org-chat');
    
        // Truncate the message content to 50 characters for display
        let truncatedMessage = message.contents.slice(0, 50);
        if (message.contents.length > 50) {
            truncatedMessage += '...';
        }
            
        // Update the latest message content
        orgChatElement.textContent = truncatedMessage || 'No messages yet...';
    })
    .catch(error => console.error('Error fetching latest org message:', error));
}

//this is for getting newly sent messages and adding them to the chat area
function updateChat() {
    messageList = document.querySelectorAll('[id^="message-"]');
    const ids = Array.from(messageList).map(element => {
    // Use a regex to ensure the ID strictly follows 'message-<number>'
    if (/^message-\d+$/.test(element.id)) {
        return parseInt(element.id.replace('message-', ''));
    }
    return null; // Return null for elements that don't match the pattern
    }).filter(id => id !== null);
    const maxId = Math.max(...ids);

    //now run the php
    fetch('chat/get_newest_messages.php?id='+orgId+'&latestMsgId='+maxId)
    .then(response => response.json())
    .then(message => {
        //change contents
        let messageContainer = document.getElementById('chat-messages');
        messageContainer.innerHTML += message.contents;

        //if a message sent by the logged in user is sent
        //scroll down to the bottom
        if (message.scrollDown) {
            document.getElementById('chat-messages').scrollTop = document.getElementById('chat-messages').scrollHeight;
        }
    })
    .catch(error => {});
}

document.addEventListener('DOMContentLoaded', function() {
    setInterval(updateOtherChatLatestMessage, 3000);
    setInterval(updateOrgChatLatestMessage, 3001);
    setInterval(updateChat, 3002);

    // update all the chat-sidebar-msg classes
    setInterval(function() {
        otherMsgs = document.getElementsByClassName('chat-sidebar-msgr');
    }, 3003);
});
//code for updating ends here

//by default to prevent lag on slower connections up to 8 messages get loaded
//this script should ensure that by the time the user scrolls up and theres
//more than 8 messages in the chat history between the users or within the
//organization chat more messages get loaded
document.getElementById('chat-messages').addEventListener('scroll', () => {
    let messageContainer = document.getElementById('chat-messages');

    // Check if we're at the top of the message container and if the total content height exceeds the container height
    if (messageContainer.scrollTop == 0) {
        const oldScrollHeight = messageContainer.scrollHeight;
        let lastDate = document.getElementsByClassName('chat-date-banner')[0].textContent;
        offset += 8;
        fetch("chat/get_more_messages.php?id="+orgId+"&offset="+offset+"&lastDate="+lastDate)
        .then(response => response.json())
        .then(message => {
            let nDates = new DOMParser().parseFromString(message.contents, 'text/html').getElementsByClassName('chat-date-banner');
            if (nDates.length > 0) {
                let nLastDate = nDates[nDates.length - 1].textContent
                let lastDateElement = document.getElementsByClassName('chat-date-banner')[0]
                if (nLastDate === lastDate) lastDateElement.parentNode.removeChild(lastDateElement);
                messageContainer.innerHTML = message.contents+messageContainer.innerHTML;
            }
            const newScrollHeight = messageContainer.scrollHeight;
            const scrollDifference = newScrollHeight - oldScrollHeight;

            // Adjust the scroll position to be just above the new messages
            messageContainer.scrollTop = scrollDifference;
        })
        .catch(error => console.error('Error:', error));
    }
});

//for sending messages, whether its by pressing enter or the submit button
document.getElementById('chatSendForm').addEventListener('submit', function(event) {
    event.preventDefault();
    let contents = document.getElementById("message-contents").value;
    if (contents !== "") {
        fetch("chat/send_message.php?message="+contents+"&id="+orgId)
        .then(response => response.json())
        .catch(error => console.error('Error:', error));
        offset += 1;
    }
    document.getElementById("chatSendForm").reset();

    //after sendin a message marked in recent-choice-chat, the message list is to start filling up
    // let recentChoiceChat = document.getElementById('recent-choice-chat');
    let recentChoiceChat = document.getElementById('recent-choice-chat');
    if (recentChoiceChat.querySelectorAll('.chat-sidebar-msgr-current')) {
        recentChoiceChat.innerHTML = "";
        // updateOtherChatLatestMessage();
        loadMessageHist();
    }
})

//delete message
function callDeleteMessage(messageid) {
    showPopup(`Are you sure you want to delete this message?
    <div class=\"blank-space\"></div>
    <div class="popup-button-container">
    <button class="popup-button" onclick="deleteMessage(`+messageid+`)">Yes</button>
    <button class="popup-button" onclick="closeButton()">No</button>
    </div>`);
}

function deleteMessage(messageid) {
    //remove from database
    fetch('chat/delete_message.php?messageid='+messageid)
    .then(response => response.json())
    .catch(error => console.error('Error:', error));

    //remove from html
    let toRemove = document.getElementById('message-'+messageid);
    if (toRemove) {
        toRemove.remove();
        document.getElementById('blank-space-'+messageid).remove();
    }
    offset -= 1;
    //check if theres no messages left
    //if true, change to the group chat

    closeButton();
}

//auto scroll messages container to bottom
document.getElementById('chat-messages').scrollTop = document.getElementById('chat-messages').scrollHeight;
</script>