<?php
if (isset($_GET['profile-id'])) {
    $profileId = $_GET['profile-id'];
} 
else {
    $profileId = $_SESSION['id'];
}

$sqlUserId = "SELECT * FROM users WHERE id='$profileId'";
$resultId = mysqli_query($conn, $sqlUserId);
$rowFromIdResult = mysqli_fetch_assoc($resultId);

if ($rowFromIdResult['verified']) {
?>
<?php echo "<button onclick=\"location.href='http://".$_SERVER['HTTP_HOST']."/dashboard?page=users'\" style=\"float: left; margin-right: 1100px;\">Return to user directory</button>" ?>
<div class="blank-space"></div>
<table border="1" class="profile-table">
    <tr>
        <!-- for pfp -->
        <td class="pfp-cell">
            <?php
                $profilePic = $rowFromIdResult['image'];

                echo '<img '.($_SESSION['id'] === $profileId ? 'style="cursor: pointer;"' : '').' class="pfp" src="http://'.$_SERVER['HTTP_HOST'].'/media/'.$profilePic.'">';
                if ($_SESSION['id'] === $profileId) {
                    echo '
                        <form class="form" id="pfpForm" action="" enctype="multipart/form-data" method="post">
                            <input type="file" name="image" id="fileInput" accept="image/*" style="display: none;">
                        </form>
                    ';
                    echo '<a id="changeProfilePic" class="change-prompt">Click to change picture</div>';
                }
            ?>
        </td>
        <td>
            <ul>
                <li>Name: <?php echo $rowFromIdResult['firstname'].' '.$rowFromIdResult['middlename'].' '.$rowFromIdResult['familyname'] ?> </li>
                <li>Birthday: <?php echo $rowFromIdResult['birthday'] ?> </li>
                <li>Organization: <?php echo ucfirst($rowFromIdResult['organization']) ?></li>
                <li>Role: <?php echo ucfirst($rowFromIdResult['role']) ?></li>
            </ul>
        </td>
    </tr>
</table>

<div class="blank-space"></div>
<div class="header-with-text">
    <h2>Bio</h2>
    <?php
        if ($_SESSION['id'] === $profileId) {
            echo "<a class=\"small-text\" id=\"changeProfileBio\" href=\"#edit\">Edit</a>";
        }
    ?>
</div>

<?php echo "<div id='bioToEdit'>".$rowFromIdResult['bio']."</div>"; ?>
<form style="display: none;" id="bioForm" class="editable" method="post">
    <textarea id="bioFormInput" name="bioText" maxlength="2048"></textarea>
    <div class="blank-space"></div>
    <button type="submit">Update</button>
</form>

<?php 
}
?>
<script>
    var changePicLink = document.getElementById('changeProfilePic');
    var fileInput = document.getElementById('fileInput');
    var changeProfileBio = document.getElementById('changeProfileBio');
    var bioForm = document.getElementById('bioForm');
    var bioToEdit = document.getElementById('bioToEdit');
    var bioFormInput = document.getElementById('bioFormInput');

    changePicLink.addEventListener('click', function(event) {
        event.preventDefault();
        fileInput.click();
    });

    fileInput.onchange = function(){
        document.getElementById("pfpForm").submit();
    };

    changeProfileBio.addEventListener('click', function(event) {
        bioForm.style.display = 'block';
        bioToEdit.style.display = 'none';
        changeProfileBio.style.display = 'none';
        bioFormInput.value = bioToEdit.innerHTML;
    });

</script>

<?php
    if (isset($_FILES["image"]["name"])) {
        $imageName = $_FILES["image"]["name"];
        $imageSize = $_FILES["image"]["size"];
        $tmpName = $_FILES["image"]["tmp_name"];

        // Image validation
        $validImageExtension = ['jpg', 'jpeg', 'png'];
        $imageExtension = explode('.', $imageName);
        $imageExtension = strtolower(end($imageExtension));
        if (!in_array($imageExtension, $validImageExtension)){
            echo
            "
            <script>
            alert('Invalid Image Extension');
            document.location.href = /dashboard?page=profile&profile-id=".$_SESSION['id'].";
            </script>
            ";
        }
        elseif ($imageSize > 1200000) {
            echo
            "
            <script>
            alert('Image Size Is Too Large');
            document.location.href = /dashboard?page=profile&profile-id=".$_SESSION['id'].";
            </script>
            ";
        }
        else {
            $newImageName = 'users/'.$_SESSION['id']." profile pic"; // Generate new image name
            $newImageName .= '.' . $imageExtension;
            $query = "UPDATE users SET image = '$newImageName' WHERE id = ".$_SESSION['id'];
            mysqli_query($conn, $query);
            move_uploaded_file($tmpName, $_SERVER['DOCUMENT_ROOT'] . '/media/' . $newImageName);
            header('Location: http://'.$_SERVER['HTTP_HOST'].'/dashboard?page=profile&profile-id='.$_SESSION['id']);
        }
    }
    if (isset($_POST['bioText'])) {
        $newBioText = mysqli_real_escape_string($conn, $_POST['bioText']);
        $query = "UPDATE users SET bio = '$newBioText' WHERE id = ".$_SESSION['id'];
        mysqli_query($conn, $query);
        header('Location: http://'.$_SERVER['HTTP_HOST'].'/dashboard?page=profile&profile-id='.$_SESSION['id']);
    }
?>