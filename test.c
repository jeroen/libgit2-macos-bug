/* Compile with: clang test.c -o test $(pkg-config --libs --cflags libgit2) */
#include <stdio.h>
#include <git2.h>

static int print_progress(unsigned int cur, unsigned int tot, size_t bytes, void *payload){
  static size_t prev = 0;
  if(prev != cur){
    prev = cur;
    fprintf(stderr, "\rTransferred %d of %d objects...", cur, tot);
    if(cur == tot)
      fprintf(stderr, "done!\n");
  }
  return 0;
}

static int fetch_progress(const git_transfer_progress *stats, void *payload){
  return print_progress(stats->received_objects, stats->total_objects, 0, NULL);
}

int main(int argc, char *argv[]) {
  git_libgit2_init();
  const char *url = "https://github.com/hadley/tidytext.git";
  git_repository *repo = NULL;
  git_clone_options clone_opts = GIT_CLONE_OPTIONS_INIT;
  clone_opts.checkout_opts.checkout_strategy = GIT_CHECKOUT_SAFE;
  clone_opts.fetch_opts.callbacks.transfer_progress = fetch_progress;
  int err = git_clone(&repo, url, "output", &clone_opts);
  if (err) {
    const git_error *info = giterr_last();
    fprintf(stderr, "%s\n", info ? info->message : "Unknown error message");
  }
  return err;
}
