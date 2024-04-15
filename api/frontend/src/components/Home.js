import React from "react";
import axios from "axios";

export function Home() {

  const [post, setPost] = React.useState(null);
  const test = "https://jsonplaceholder.typicode.com/posts/1";

  React.useEffect(() => {
    axios.get(test).then((response) => {
      setPost(response.data);
    });
  }, []);

  if (!post) return null;

  return (
    <div className="container-fluid">
      <div className="row">
        <div id="home-wrap" className="col-md-12">
          <h1>{post.title}</h1>
          <p>{post.body}</p>
        </div>
      </div>
    </div>
  );
}
