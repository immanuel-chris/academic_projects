<?php
$profileId = $_SESSION['id'];
$sqlUserId = "SELECT * FROM users WHERE id='$profileId'";
$resultId = mysqli_query($conn, $sqlUserId);
$rowFromIdResult = mysqli_fetch_assoc($resultId);
?>

<?php if (isset($_GET['error'])) { ?>
    <p class="error"><?php echo $_GET['error']; ?></p>
<?php } else if (isset($_GET['success'])) { ?>
    <p class="success"><?php echo $_GET['success']; ?></p>
<?php } ?>

<h2>Change Info</h2>
<form class="settings" action="settings/change_info.php" method="post">
    <div class="settings-form-row">
        <label>E-mail</label>
        <input type="text" name="email" placeholder="<?php echo $rowFromIdResult['email']; ?>">
    </div>

    <div class="settings-form-row">
        <label>First Name</label>
        <input type="text" name="firstname" placeholder="<?php echo $rowFromIdResult['firstname']; ?>">
    </div>
    
    <div class="settings-form-row">
        <label>Middle Name</label>
        <input type="text" name="middlename" placeholder="<?php echo $rowFromIdResult['middlename']; ?>">
    </div>
    
    <div class="settings-form-row">
        <label>Family Name</label>
        <input type="text" name="familyname" placeholder="<?php echo $rowFromIdResult['familyname']; ?>">
    </div>

    <button type="submit">Change</button>
</form>

<h2>Change Password</h2>
<form class="settings" action="settings/change_password.php" method="post">
    <div class="settings-form-row">
        <label>Current Password</label>
        <input type="password" name="currentpassword">
    </div>

    <div class="settings-form-row">
        <label>New Password</label>
        <input type="password" name="newpassword">
    </div>

    <div class="settings-form-row">
        <label>Re-enter New Password</label>
        <input type="password" name="renewpassword">
    </div>

    <button type="submit">Change</button>
</form>