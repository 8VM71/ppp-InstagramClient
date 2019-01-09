using Microsoft.AspNetCore.Mvc;
using Newtonsoft.Json.Linq;
using System;

namespace CalculationWebService.Controllers
{
    [Route("api/calculate")]
    [ApiController]
    public class ValuesController : ControllerBase
    {
        // GET api/values/{}
        [HttpGet("{json}")]
        public ActionResult<JObject> Get(string json)
        {
            dynamic inputJson = JObject.Parse(json);
            
            double photoFactor = 1.0;
            double postFactor = 1.0;

            if (inputJson.ContainsKey("factors"))
            {
                photoFactor = inputJson.factors.photo;
                postFactor = inputJson.factors.post;
            }

            double photoRate = 0;
            {
                int totalCount = inputJson.photos.totalCount;
                int shownCount = inputJson.photos.shownCount;
                int likes = inputJson.photos.likes;
                int reposts = inputJson.photos.reposts;

                if (shownCount > 0)
                    photoRate = ((likes + reposts) / shownCount) * totalCount / shownCount;
            }

            double postsRate = 0.0;
            {
                int totalCount = inputJson.posts.totalCount;
                int shownCount = inputJson.posts.shownCount;
                int likes = inputJson.posts.likes;
                int reposts = inputJson.posts.reposts;
                int comments = inputJson.posts.comments;

                if (shownCount > 0)
                    postsRate = ((likes + reposts + comments) / shownCount) * totalCount / shownCount;
            }

            double rate = photoFactor * photoRate + postFactor * postsRate;

            Console.WriteLine("Rate = ", rate);

            return JObject.FromObject(new
            {
                result = rate
            });
        }
    }
}
