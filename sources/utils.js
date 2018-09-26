.pragma library

function combineUrl(url,params) {
    if(params.length == 0)
        return url;

    url += '?'
    for (var param in params) {
        url += '&%1=%2'.arg(param).arg(params[param])
    }
    return url
}

