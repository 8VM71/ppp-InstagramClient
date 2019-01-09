using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Net.Http.Headers;
using Microsoft.AspNetCore.Mvc;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace BasicsWebService.Controllers
{
    [Route("api/user/{id}/info")]
    [ApiController]
    public class ValuesController : ControllerBase
    {
       
        private string baseUri = "https://api.vk.com/method/";

        // GET api/values/179521318
        //[HttpGet("{id}")]
        public ActionResult<JObject> Get(string id)
        {
            Dictionary<string, string> apiParams = new Dictionary<string, string>
            {
                {"owner_id", id},
                {"count", "100" },
                {"extended", "1"},
                {"access_token", "eab2c2512a9525259111b83f1ae574e1783b9769a175611b41185391cdd77ed49e375d817bfc30dc08ecb" },
                { "v", "5.8"}
            };

            dynamic photosJson = SendRequestAsync("photos.getAll", apiParams);

            apiParams.Add("filter", "owner");
            apiParams.Remove("extended");
            dynamic postsJson = SendRequestAsync("wall.get", apiParams);

            if ((photosJson == null || postsJson.ContainsKey("error")) && (postsJson == null || postsJson.ContainsKey("error")))
            {
                return null;
            }


            JObject photoParams = new JObject();
            {
                var items = photosJson.response.items;

                int total = photosJson.response.count;
                int likesCount = 0;
                int repostsCount = 0;

                foreach (var item in items)
                {
                    likesCount += item.likes.count.ToObject<int>();
                    repostsCount += item.reposts.count.ToObject<int>();
                }

                photoParams = JObject.FromObject(new
                {
                    totalCount = total,
                    shownCount = items.Count,
                    likes = likesCount,
                    reposts = repostsCount
                });
            }

            JObject postsParams = new JObject();
            {
                var items = postsJson.response.items;

                int total = postsJson.response.count;
                int likesCount = 0;
                int repostsCount = 0;
                int commentsCount = 0;

                foreach (var item in items)
                {
                    likesCount += item.likes.count.ToObject<int>();
                    repostsCount += item.reposts.count.ToObject<int>();
                    commentsCount += item.comments.count.ToObject<int>();
                }

                postsParams = JObject.FromObject(new
                {
                    totalCount = total,
                    shownCount = items.Count,
                    likes = likesCount,
                    reposts = repostsCount,
                    comments = commentsCount
                });
            }

            return JObject.FromObject(new
            {
                photos = photoParams,
                posts = postsParams
            });
        }

        private JObject SendRequestAsync(string apiMethod, Dictionary<string, string> apiParams)
        {
            using (var client = new HttpClient())
            {
                client.BaseAddress = new Uri(baseUri + apiMethod);
                client.DefaultRequestHeaders.Accept.Add(new MediaTypeWithQualityHeaderValue("application/json"));

                string stringParams = String.Format("?{0}", string.Join("&", apiParams.Select(e => e.Key + "=" + e.Value).ToArray()));

                var response = client.GetStringAsync(stringParams).Result;
                try
                {
                    JObject jsonObject = JObject.Parse(response);
                    return jsonObject;
                }
                catch (JsonReaderException ex)
                {
                    Console.WriteLine(ex.ToString());
                    return null;
                }
            }
        }
    }
}
