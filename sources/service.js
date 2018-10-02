.import "utils.js" as Utils

//var token = "65864d4e5c038b45da86a38e1f00b4b245095dbad3f1637d3ffae8c3bf35be6633be403820126dcae4294";

function Service() {

}

Service.prototype.setToken = function(token) {
    this.token = token
}


Service.prototype.sendGetRequest = function(url, callback) {
    console.info("Get", url)
    var request = new XMLHttpRequest();
    request.open("GET", url);
    request.onreadystatechange = function() {
        if (request.readyState === XMLHttpRequest.DONE) {
            if (request.status === 200) {
                var jsonObject = JSON.parse(request.responseText);
                callback({
                             success: true,
                             data: jsonObject
                         })
            } else {
                callback({
                             success: false,
                             error: request.status,
                             errorString: "HTTP(%1): %2 %3".arg(url).arg(request.status).arg(request.statusText)
                         })
            }
        }
    }
    request.setRequestHeader('Content-Type', 'application/json');
    request.send();
}

Service.prototype.getAppPermissions = function(userId, callback) {
    var url = "https://api.vk.com/method/account.getAppPermissions";
    var queryParams = {
        user_id : userId,
        v : "5.8",
        access_token : this.token
    };

    url = Utils.combineUrl(url, queryParams);

    this.sendGetRequest(url, callback)
}

Service.prototype.searchUsers = function(searchQuery, callback) {
    var url = "https://api.vk.com/method/users.search";
    var queryParams = {
        q : searchQuery,
        v : "5.8",
        fields : "photo_big,screen_name,city,followers_count",
        access_token : this.token
    };

    url = Utils.combineUrl(url, queryParams);

    this.sendGetRequest(url, callback)
}

Service.prototype.getUserInfo = function(userId, callback) {
    var url = "https://api.vk.com/method/users.get";
    var queryParams = {
        user_ids : userId,
        v : "5.8",
        fields : "photo_id,verified,sex,bdate,city,country,home_town,has_photo,photo_50,photo_100,photo_200_orig,photo_200,photo_400_orig,photo_max,photo_max_orig,online,domain,has_mobile,contacts,site,education,universities,schools,status,last_seen,followers_count,common_count,occupation,nickname,relatives,relation,personal,connections,exports,activities,interests,music,movies,tv,books,games,about,quotes,can_post,can_see_all_posts,can_see_audio,can_write_private_message,can_send_friend_request,is_favorite,is_hidden_from_feed,timezone,screen_name,maiden_name,crop_photo,is_friend,friend_status,career,military,blacklisted,blacklisted_by_me",
        access_token : this.token
    };

    url = Utils.combineUrl(url, queryParams);

    this.sendGetRequest(url, callback)
}

Service.prototype.getUserPhotos = function(userId, callback) {
    var url = "https://api.vk.com/method/photos.getAll";
    var queryParams = {
        owner_id : userId,
        count: "100",
        extended: "1",
        v : "5.8",
        access_token : this.token
    };

    url = Utils.combineUrl(url, queryParams);

    this.sendGetRequest(url, callback)
}
