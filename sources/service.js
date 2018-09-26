.import "utils.js" as Utils

var token = "65864d4e5c038b45da86a38e1f00b4b245095dbad3f1637d3ffae8c3bf35be6633be403820126dcae4294";

function Service() {

}

Service.prototype.searchUsers = function(searchQuery) {
    var url = "https://api.vk.com/method/users.search";
    var queryParams = {
        q : searchQuery,
        v : "5.8",
        fields : "photo_big,screen_name,city,followers_count",
        access_token : token
    };

    url = Utils.combineUrl(url, queryParams);


    var request = new XMLHttpRequest();

    request.open("GET", url);

    request.onreadystatechange = function() {

        if (request.readyState === XMLHttpRequest.DONE) {

            if (request.status === 200) {

                console.debug("response text", request.responseText);

                var jsonObject = JSON.parse(request.responseText);

                console.debug("response json", jsonObject);


            } else if(request.status === 0) {

                console.error("HTTP(%1): %2 %3".arg(url).arg(request.status).arg(request.statusText));


            } else {
                var message = 'Status %1 %2'.arg(request.status).arg(request.statusText);

            }

        }
    }

    request.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
    request.send();

}
