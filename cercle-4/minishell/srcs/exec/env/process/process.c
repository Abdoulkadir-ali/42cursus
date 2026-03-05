

#include "exec.h"

int	process_export_arg(char *arg, t_shell_state *state)
{
	t_export_ctx	ctx;

	ft_bzero(&ctx, sizeof(ctx));
	parse_export_arg(arg, &ctx);
	if (!is_valid_ident(ctx.key))
		return (report_invalid_identifier(arg, &ctx));
	ctx.idx = get_env_index(ctx.key, state);
	if (ctx.idx != -1)
		return (process_existing_export(&ctx, &state->envp));
	else
		return (process_new_export(&ctx, &state->envp));
}
